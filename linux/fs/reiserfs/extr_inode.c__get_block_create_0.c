#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct item_head {int dummy; } ;
struct inode {scalar_t__ i_size; TYPE_2__* i_sb; } ;
struct cpu_key {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  scalar_t__ sector_t ;
typedef  int loff_t ;
typedef  scalar_t__ b_blocknr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_11__ {int s_blocksize; } ;
struct TYPE_10__ {int pos_in_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 int EIO ; 
 int ENOENT ; 
 int GET_BLOCK_NO_HOLE ; 
 int GET_BLOCK_READ_DIRECT ; 
 int /*<<< orphan*/  INITIALIZE_PATH (TYPE_1__) ; 
 int IO_ERROR ; 
 int PAGE_SIZE ; 
 int PATH_LAST_POSITION (TYPE_1__*) ; 
 int POSITION_FOUND ; 
 scalar_t__ PageUptodate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ANY ; 
 int UNFM_P_SIZE ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  copy_item_head (struct item_head*,struct item_head*) ; 
 int cpu_key_k_offset (struct cpu_key*) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 scalar_t__ get_block_num (int /*<<< orphan*/ *,int) ; 
 struct buffer_head* get_last_bh (TYPE_1__*) ; 
 scalar_t__ ih_item_body (struct buffer_head*,struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 int /*<<< orphan*/  is_direct_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 scalar_t__ kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int le_ih_k_offset (struct item_head*) ; 
 int /*<<< orphan*/  make_cpu_key (struct cpu_key*,struct inode*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ path ; 
 int /*<<< orphan*/  pathrelse (TYPE_1__*) ; 
 int search_for_position_by_key (TYPE_2__*,struct cpu_key*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_buffer_boundary (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_cpu_key_k_offset (struct cpu_key*,int) ; 
 struct item_head* tp_item_head (TYPE_1__*) ; 

__attribute__((used)) static int _get_block_create_0(struct inode *inode, sector_t block,
			       struct buffer_head *bh_result, int args)
{
	INITIALIZE_PATH(path);
	struct cpu_key key;
	struct buffer_head *bh;
	struct item_head *ih, tmp_ih;
	b_blocknr_t blocknr;
	char *p = NULL;
	int chars;
	int ret;
	int result;
	int done = 0;
	unsigned long offset;

	/* prepare the key to look for the 'block'-th block of file */
	make_cpu_key(&key, inode,
		     (loff_t) block * inode->i_sb->s_blocksize + 1, TYPE_ANY,
		     3);

	result = search_for_position_by_key(inode->i_sb, &key, &path);
	if (result != POSITION_FOUND) {
		pathrelse(&path);
		if (p)
			kunmap(bh_result->b_page);
		if (result == IO_ERROR)
			return -EIO;
		/*
		 * We do not return -ENOENT if there is a hole but page is
		 * uptodate, because it means that there is some MMAPED data
		 * associated with it that is yet to be written to disk.
		 */
		if ((args & GET_BLOCK_NO_HOLE)
		    && !PageUptodate(bh_result->b_page)) {
			return -ENOENT;
		}
		return 0;
	}

	bh = get_last_bh(&path);
	ih = tp_item_head(&path);
	if (is_indirect_le_ih(ih)) {
		__le32 *ind_item = (__le32 *) ih_item_body(bh, ih);

		/*
		 * FIXME: here we could cache indirect item or part of it in
		 * the inode to avoid search_by_key in case of subsequent
		 * access to file
		 */
		blocknr = get_block_num(ind_item, path.pos_in_item);
		ret = 0;
		if (blocknr) {
			map_bh(bh_result, inode->i_sb, blocknr);
			if (path.pos_in_item ==
			    ((ih_item_len(ih) / UNFM_P_SIZE) - 1)) {
				set_buffer_boundary(bh_result);
			}
		} else
			/*
			 * We do not return -ENOENT if there is a hole but
			 * page is uptodate, because it means that there is
			 * some MMAPED data associated with it that is
			 * yet to be written to disk.
			 */
		if ((args & GET_BLOCK_NO_HOLE)
			    && !PageUptodate(bh_result->b_page)) {
			ret = -ENOENT;
		}

		pathrelse(&path);
		if (p)
			kunmap(bh_result->b_page);
		return ret;
	}
	/* requested data are in direct item(s) */
	if (!(args & GET_BLOCK_READ_DIRECT)) {
		/*
		 * we are called by bmap. FIXME: we can not map block of file
		 * when it is stored in direct item(s)
		 */
		pathrelse(&path);
		if (p)
			kunmap(bh_result->b_page);
		return -ENOENT;
	}

	/*
	 * if we've got a direct item, and the buffer or page was uptodate,
	 * we don't want to pull data off disk again.  skip to the
	 * end, where we map the buffer and return
	 */
	if (buffer_uptodate(bh_result)) {
		goto finished;
	} else
		/*
		 * grab_tail_page can trigger calls to reiserfs_get_block on
		 * up to date pages without any buffers.  If the page is up
		 * to date, we don't want read old data off disk.  Set the up
		 * to date bit on the buffer instead and jump to the end
		 */
	if (!bh_result->b_page || PageUptodate(bh_result->b_page)) {
		set_buffer_uptodate(bh_result);
		goto finished;
	}
	/* read file tail into part of page */
	offset = (cpu_key_k_offset(&key) - 1) & (PAGE_SIZE - 1);
	copy_item_head(&tmp_ih, ih);

	/*
	 * we only want to kmap if we are reading the tail into the page.
	 * this is not the common case, so we don't kmap until we are
	 * sure we need to.  But, this means the item might move if
	 * kmap schedules
	 */
	if (!p)
		p = (char *)kmap(bh_result->b_page);

	p += offset;
	memset(p, 0, inode->i_sb->s_blocksize);
	do {
		if (!is_direct_le_ih(ih)) {
			BUG();
		}
		/*
		 * make sure we don't read more bytes than actually exist in
		 * the file.  This can happen in odd cases where i_size isn't
		 * correct, and when direct item padding results in a few
		 * extra bytes at the end of the direct item
		 */
		if ((le_ih_k_offset(ih) + path.pos_in_item) > inode->i_size)
			break;
		if ((le_ih_k_offset(ih) - 1 + ih_item_len(ih)) > inode->i_size) {
			chars =
			    inode->i_size - (le_ih_k_offset(ih) - 1) -
			    path.pos_in_item;
			done = 1;
		} else {
			chars = ih_item_len(ih) - path.pos_in_item;
		}
		memcpy(p, ih_item_body(bh, ih) + path.pos_in_item, chars);

		if (done)
			break;

		p += chars;

		/*
		 * we done, if read direct item is not the last item of
		 * node FIXME: we could try to check right delimiting key
		 * to see whether direct item continues in the right
		 * neighbor or rely on i_size
		 */
		if (PATH_LAST_POSITION(&path) != (B_NR_ITEMS(bh) - 1))
			break;

		/* update key to look for the next piece */
		set_cpu_key_k_offset(&key, cpu_key_k_offset(&key) + chars);
		result = search_for_position_by_key(inode->i_sb, &key, &path);
		if (result != POSITION_FOUND)
			/* i/o error most likely */
			break;
		bh = get_last_bh(&path);
		ih = tp_item_head(&path);
	} while (1);

	flush_dcache_page(bh_result->b_page);
	kunmap(bh_result->b_page);

finished:
	pathrelse(&path);

	if (result == IO_ERROR)
		return -EIO;

	/*
	 * this buffer has valid data, but isn't valid for io.  mapping it to
	 * block #0 tells the rest of reiserfs it just has a tail in it
	 */
	map_bh(bh_result, inode->i_sb, 0);
	set_buffer_uptodate(bh_result);
	return 0;
}