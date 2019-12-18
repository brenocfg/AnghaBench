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
struct z_erofs_map_header {int h_algorithmtype; int h_clusterbits; int /*<<< orphan*/  h_advise; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct erofs_inode {scalar_t__ datalayout; int* z_algorithmtype; int z_logical_clusterbits; int* z_physical_clusterbits; int /*<<< orphan*/  flags; int /*<<< orphan*/  nid; int /*<<< orphan*/  z_advise; scalar_t__ xattr_isize; scalar_t__ inode_isize; } ;
typedef  int /*<<< orphan*/  erofs_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 struct erofs_inode* EROFS_I (struct inode*) ; 
 scalar_t__ EROFS_INODE_FLAT_COMPRESSION_LEGACY ; 
 int /*<<< orphan*/  EROFS_I_BL_Z_BIT ; 
 int /*<<< orphan*/  EROFS_I_Z_INITED_BIT ; 
 int /*<<< orphan*/  EROFS_SB (struct super_block* const) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int LOG_BLOCK_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int Z_EROFS_COMPRESSION_MAX ; 
 int /*<<< orphan*/  clear_and_wake_up_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  erofs_blknr (int /*<<< orphan*/ ) ; 
 int erofs_blkoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_err (struct super_block* const,char*,int,int /*<<< orphan*/ ) ; 
 struct page* erofs_get_meta_page (struct super_block* const,int /*<<< orphan*/ ) ; 
 scalar_t__ iloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ wait_on_bit_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_inode_lazy(struct inode *inode)
{
	struct erofs_inode *const vi = EROFS_I(inode);
	struct super_block *const sb = inode->i_sb;
	int err;
	erofs_off_t pos;
	struct page *page;
	void *kaddr;
	struct z_erofs_map_header *h;

	if (test_bit(EROFS_I_Z_INITED_BIT, &vi->flags))
		return 0;

	if (wait_on_bit_lock(&vi->flags, EROFS_I_BL_Z_BIT, TASK_KILLABLE))
		return -ERESTARTSYS;

	err = 0;
	if (test_bit(EROFS_I_Z_INITED_BIT, &vi->flags))
		goto out_unlock;

	DBG_BUGON(vi->datalayout == EROFS_INODE_FLAT_COMPRESSION_LEGACY);

	pos = ALIGN(iloc(EROFS_SB(sb), vi->nid) + vi->inode_isize +
		    vi->xattr_isize, 8);
	page = erofs_get_meta_page(sb, erofs_blknr(pos));
	if (IS_ERR(page)) {
		err = PTR_ERR(page);
		goto out_unlock;
	}

	kaddr = kmap_atomic(page);

	h = kaddr + erofs_blkoff(pos);
	vi->z_advise = le16_to_cpu(h->h_advise);
	vi->z_algorithmtype[0] = h->h_algorithmtype & 15;
	vi->z_algorithmtype[1] = h->h_algorithmtype >> 4;

	if (vi->z_algorithmtype[0] >= Z_EROFS_COMPRESSION_MAX) {
		erofs_err(sb, "unknown compression format %u for nid %llu, please upgrade kernel",
			  vi->z_algorithmtype[0], vi->nid);
		err = -EOPNOTSUPP;
		goto unmap_done;
	}

	vi->z_logical_clusterbits = LOG_BLOCK_SIZE + (h->h_clusterbits & 7);
	vi->z_physical_clusterbits[0] = vi->z_logical_clusterbits +
					((h->h_clusterbits >> 3) & 3);

	if (vi->z_physical_clusterbits[0] != LOG_BLOCK_SIZE) {
		erofs_err(sb, "unsupported physical clusterbits %u for nid %llu, please upgrade kernel",
			  vi->z_physical_clusterbits[0], vi->nid);
		err = -EOPNOTSUPP;
		goto unmap_done;
	}

	vi->z_physical_clusterbits[1] = vi->z_logical_clusterbits +
					((h->h_clusterbits >> 5) & 7);
	set_bit(EROFS_I_Z_INITED_BIT, &vi->flags);
unmap_done:
	kunmap_atomic(kaddr);
	unlock_page(page);
	put_page(page);
out_unlock:
	clear_and_wake_up_bit(EROFS_I_BL_Z_BIT, &vi->flags);
	return err;
}