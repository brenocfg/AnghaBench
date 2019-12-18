#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct page {int /*<<< orphan*/  index; } ;
struct inode {struct super_block* i_sb; } ;
struct erofs_map_blocks {int m_flags; scalar_t__ m_plen; scalar_t__ m_llen; int /*<<< orphan*/  m_pa; int /*<<< orphan*/  m_la; } ;
struct TYPE_2__ {int bi_sector; int bi_size; } ;
struct bio {int bi_max_vecs; TYPE_1__ bi_iter; int /*<<< orphan*/  bi_opf; int /*<<< orphan*/  bi_end_io; } ;
struct address_space {struct inode* host; } ;
typedef  int sector_t ;
typedef  scalar_t__ erofs_off_t ;
typedef  scalar_t__ erofs_blk_t ;

/* Variables and functions */
 unsigned int BIO_MAX_PAGES ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 unsigned int DIV_ROUND_UP (void*,int) ; 
 int /*<<< orphan*/  EROFS_GET_BLOCKS_RAW ; 
 int EROFS_MAP_MAPPED ; 
 int EROFS_MAP_META ; 
 struct bio* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int LOG_SECTORS_PER_BLOCK ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blknr_to_addr (scalar_t__) ; 
 scalar_t__ erofs_blknr (int /*<<< orphan*/ ) ; 
 int erofs_blkoff (int /*<<< orphan*/ ) ; 
 struct page* erofs_get_meta_page (struct super_block*,scalar_t__) ; 
 int erofs_map_blocks (struct inode* const,struct erofs_map_blocks*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_readendio ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct bio *erofs_read_raw_page(struct bio *bio,
					      struct address_space *mapping,
					      struct page *page,
					      erofs_off_t *last_block,
					      unsigned int nblocks,
					      bool ra)
{
	struct inode *const inode = mapping->host;
	struct super_block *const sb = inode->i_sb;
	erofs_off_t current_block = (erofs_off_t)page->index;
	int err;

	DBG_BUGON(!nblocks);

	if (PageUptodate(page)) {
		err = 0;
		goto has_updated;
	}

	/* note that for readpage case, bio also equals to NULL */
	if (bio &&
	    /* not continuous */
	    *last_block + 1 != current_block) {
submit_bio_retry:
		submit_bio(bio);
		bio = NULL;
	}

	if (!bio) {
		struct erofs_map_blocks map = {
			.m_la = blknr_to_addr(current_block),
		};
		erofs_blk_t blknr;
		unsigned int blkoff;

		err = erofs_map_blocks(inode, &map, EROFS_GET_BLOCKS_RAW);
		if (err)
			goto err_out;

		/* zero out the holed page */
		if (!(map.m_flags & EROFS_MAP_MAPPED)) {
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

			ipage = erofs_get_meta_page(inode->i_sb, blknr);

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

		bio = bio_alloc(GFP_NOIO, nblocks);

		bio->bi_end_io = erofs_readendio;
		bio_set_dev(bio, sb->s_bdev);
		bio->bi_iter.bi_sector = (sector_t)blknr <<
			LOG_SECTORS_PER_BLOCK;
		bio->bi_opf = REQ_OP_READ;
	}

	err = bio_add_page(bio, page, PAGE_SIZE, 0);
	/* out of the extent or bio is full */
	if (err < PAGE_SIZE)
		goto submit_bio_retry;

	*last_block = current_block;

	/* shift in advance in case of it followed by too many gaps */
	if (bio->bi_iter.bi_size >= bio->bi_max_vecs * PAGE_SIZE) {
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
	if (bio)
submit_bio_out:
		submit_bio(bio);
	return err ? ERR_PTR(err) : NULL;
}