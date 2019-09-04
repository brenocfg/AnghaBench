#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int /*<<< orphan*/  index; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct erofs_map_blocks {int m_flags; scalar_t__ m_plen; scalar_t__ m_llen; int /*<<< orphan*/  m_pa; int /*<<< orphan*/  m_la; } ;
struct bio {scalar_t__ bi_vcnt; scalar_t__ bi_max_vecs; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ erofs_off_t ;
typedef  int /*<<< orphan*/  erofs_blk_t ;

/* Variables and functions */
 unsigned int BIO_MAX_PAGES ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 unsigned int DIV_ROUND_UP (void*,int) ; 
 int /*<<< orphan*/  EROFS_GET_BLOCKS_RAW ; 
 int EROFS_MAP_MAPPED ; 
 int EROFS_MAP_META ; 
 struct bio* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __submit_bio (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blknr_to_addr (scalar_t__) ; 
 scalar_t__ cleancache_get_page (struct page*) ; 
 int /*<<< orphan*/  erofs_blknr (int /*<<< orphan*/ ) ; 
 int erofs_blkoff (int /*<<< orphan*/ ) ; 
 struct page* erofs_get_meta_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int erofs_map_blocks (struct inode*,struct erofs_map_blocks*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,void*) ; 
 struct bio* prepare_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  read_endio ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct bio *erofs_read_raw_page(
	struct bio *bio,
	struct address_space *mapping,
	struct page *page,
	erofs_off_t *last_block,
	unsigned nblocks,
	bool ra)
{
	struct inode *inode = mapping->host;
	erofs_off_t current_block = (erofs_off_t)page->index;
	int err;

	DBG_BUGON(!nblocks);

	if (PageUptodate(page)) {
		err = 0;
		goto has_updated;
	}

	if (cleancache_get_page(page) == 0) {
		err = 0;
		SetPageUptodate(page);
		goto has_updated;
	}

	/* note that for readpage case, bio also equals to NULL */
	if (bio != NULL &&
		/* not continuous */
		*last_block + 1 != current_block) {
submit_bio_retry:
		__submit_bio(bio, REQ_OP_READ, 0);
		bio = NULL;
	}

	if (bio == NULL) {
		struct erofs_map_blocks map = {
			.m_la = blknr_to_addr(current_block),
		};
		erofs_blk_t blknr;
		unsigned blkoff;

		err = erofs_map_blocks(inode, &map, EROFS_GET_BLOCKS_RAW);
		if (unlikely(err))
			goto err_out;

		/* zero out the holed page */
		if (unlikely(!(map.m_flags & EROFS_MAP_MAPPED))) {
			zero_user_segment(page, 0, PAGE_SIZE);
			SetPageUptodate(page);

			/* imply err = 0, see erofs_map_blocks */
			goto has_updated;
		}

		/* for RAW access mode, m_plen must be equal to m_llen */
		DBG_BUGON(map.m_plen != map.m_llen);

		blknr = erofs_blknr(map.m_pa);
		blkoff = erofs_blkoff(map.m_pa);

		/* deal with inline page */
		if (map.m_flags & EROFS_MAP_META) {
			void *vsrc, *vto;
			struct page *ipage;

			DBG_BUGON(map.m_plen > PAGE_SIZE);

			ipage = erofs_get_meta_page(inode->i_sb, blknr, 0);

			if (IS_ERR(ipage)) {
				err = PTR_ERR(ipage);
				goto err_out;
			}

			vsrc = kmap_atomic(ipage);
			vto = kmap_atomic(page);
			memcpy(vto, vsrc + blkoff, map.m_plen);
			memset(vto + map.m_plen, 0, PAGE_SIZE - map.m_plen);
			kunmap_atomic(vto);
			kunmap_atomic(vsrc);
			flush_dcache_page(page);

			SetPageUptodate(page);
			/* TODO: could we unlock the page earlier? */
			unlock_page(ipage);
			put_page(ipage);

			/* imply err = 0, see erofs_map_blocks */
			goto has_updated;
		}

		/* pa must be block-aligned for raw reading */
		DBG_BUGON(erofs_blkoff(map.m_pa));

		/* max # of continuous pages */
		if (nblocks > DIV_ROUND_UP(map.m_plen, PAGE_SIZE))
			nblocks = DIV_ROUND_UP(map.m_plen, PAGE_SIZE);
		if (nblocks > BIO_MAX_PAGES)
			nblocks = BIO_MAX_PAGES;

		bio = prepare_bio(inode->i_sb, blknr, nblocks, read_endio);
	}

	err = bio_add_page(bio, page, PAGE_SIZE, 0);
	/* out of the extent or bio is full */
	if (err < PAGE_SIZE)
		goto submit_bio_retry;

	*last_block = current_block;

	/* shift in advance in case of it followed by too many gaps */
	if (unlikely(bio->bi_vcnt >= bio->bi_max_vecs)) {
		/* err should reassign to 0 after submitting */
		err = 0;
		goto submit_bio_out;
	}

	return bio;

err_out:
	/* for sync reading, set page error immediately */
	if (!ra) {
		SetPageError(page);
		ClearPageUptodate(page);
	}
has_updated:
	unlock_page(page);

	/* if updated manually, continuous pages has a gap */
	if (bio != NULL)
submit_bio_out:
		__submit_bio(bio, REQ_OP_READ, 0);

	return unlikely(err) ? ERR_PTR(err) : NULL;
}