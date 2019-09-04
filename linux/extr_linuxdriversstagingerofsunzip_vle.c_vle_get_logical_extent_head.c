#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  blkaddr; int /*<<< orphan*/ * delta; } ;
struct z_erofs_vle_decompressed_index {TYPE_1__ di_u; int /*<<< orphan*/  di_clusterofs; } ;
struct page {scalar_t__ index; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  unsigned long long erofs_off_t ;
typedef  scalar_t__ erofs_blk_t ;
struct TYPE_4__ {unsigned int clusterbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 unsigned int EROFS_MAP_ZIPPED ; 
 TYPE_2__* EROFS_SB (int /*<<< orphan*/ ) ; 
#define  Z_EROFS_VLE_CLUSTER_TYPE_HEAD 130 
#define  Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD 129 
#define  Z_EROFS_VLE_CLUSTER_TYPE_PLAIN 128 
 struct page* erofs_get_meta_page (int /*<<< orphan*/ ,scalar_t__,int) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 unsigned int const le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int vle_cluster_type (struct z_erofs_vle_decompressed_index*) ; 
 scalar_t__ vle_extent_blkaddr (struct inode*,unsigned int) ; 
 int vle_extent_blkoff (struct inode*,unsigned int) ; 

__attribute__((used)) static erofs_off_t vle_get_logical_extent_head(
	struct inode *inode,
	struct page **page_iter,
	void **kaddr_iter,
	unsigned lcn,	/* logical cluster number */
	erofs_blk_t *pcn,
	unsigned *flags)
{
	/* for extent meta */
	struct page *page = *page_iter;
	erofs_blk_t blkaddr = vle_extent_blkaddr(inode, lcn);
	struct z_erofs_vle_decompressed_index *di;
	unsigned long long ofs;
	const unsigned int clusterbits = EROFS_SB(inode->i_sb)->clusterbits;
	const unsigned int clustersize = 1 << clusterbits;
	unsigned int delta0;

	if (page->index != blkaddr) {
		kunmap_atomic(*kaddr_iter);
		unlock_page(page);
		put_page(page);

		*page_iter = page = erofs_get_meta_page(inode->i_sb,
			blkaddr, false);
		*kaddr_iter = kmap_atomic(page);
	}

	di = *kaddr_iter + vle_extent_blkoff(inode, lcn);
	switch (vle_cluster_type(di)) {
	case Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD:
		delta0 = le16_to_cpu(di->di_u.delta[0]);
		DBG_BUGON(!delta0);
		DBG_BUGON(lcn < delta0);

		ofs = vle_get_logical_extent_head(inode,
			page_iter, kaddr_iter,
			lcn - delta0, pcn, flags);
		break;
	case Z_EROFS_VLE_CLUSTER_TYPE_PLAIN:
		*flags ^= EROFS_MAP_ZIPPED;
	case Z_EROFS_VLE_CLUSTER_TYPE_HEAD:
		/* clustersize should be a power of two */
		ofs = ((unsigned long long)lcn << clusterbits) +
			(le16_to_cpu(di->di_clusterofs) & (clustersize - 1));
		*pcn = le32_to_cpu(di->di_u.blkaddr);
		break;
	default:
		BUG_ON(1);
	}
	return ofs;
}