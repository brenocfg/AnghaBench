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
typedef  unsigned int u64 ;
struct ufs_sb_private_info {unsigned int s_fpbmask; unsigned int s_fpb; } ;
struct ufs_inode_info {unsigned int i_lastfrag; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 unsigned int ufs_fragstoblks (unsigned int) ; 
 void* ufs_get_direct_data_ptr (struct ufs_sb_private_info*,struct ufs_inode_info*,unsigned int) ; 
 unsigned int ufs_new_fragments (struct inode*,void*,unsigned int,int /*<<< orphan*/ ,unsigned int,int*,struct page*) ; 

__attribute__((used)) static bool
ufs_extend_tail(struct inode *inode, u64 writes_to,
		  int *err, struct page *locked_page)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned lastfrag = ufsi->i_lastfrag;	/* it's a short file, so unsigned is enough */
	unsigned block = ufs_fragstoblks(lastfrag);
	unsigned new_size;
	void *p;
	u64 tmp;

	if (writes_to < (lastfrag | uspi->s_fpbmask))
		new_size = (writes_to & uspi->s_fpbmask) + 1;
	else
		new_size = uspi->s_fpb;

	p = ufs_get_direct_data_ptr(uspi, ufsi, block);
	tmp = ufs_new_fragments(inode, p, lastfrag, ufs_data_ptr_to_cpu(sb, p),
				new_size - (lastfrag & uspi->s_fpbmask), err,
				locked_page);
	return tmp != 0;
}