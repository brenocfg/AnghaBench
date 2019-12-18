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
struct inode {int dummy; } ;
typedef  int pgoff_t ;
typedef  int block_t ;

/* Variables and functions */
 int ADDRS_PER_BLOCK (struct inode*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __clone_blkaddrs (struct inode*,struct inode*,int*,int*,int,int,int,int) ; 
 int __read_out_blkaddrs (struct inode*,int*,int*,int,int) ; 
 int /*<<< orphan*/  __roll_back_blkaddrs (struct inode*,int*,int*,int,int) ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int* f2fs_kvzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int*) ; 
 int min (int,int) ; 

__attribute__((used)) static int __exchange_data_block(struct inode *src_inode,
			struct inode *dst_inode, pgoff_t src, pgoff_t dst,
			pgoff_t len, bool full)
{
	block_t *src_blkaddr;
	int *do_replace;
	pgoff_t olen;
	int ret;

	while (len) {
		olen = min((pgoff_t)4 * ADDRS_PER_BLOCK(src_inode), len);

		src_blkaddr = f2fs_kvzalloc(F2FS_I_SB(src_inode),
					array_size(olen, sizeof(block_t)),
					GFP_KERNEL);
		if (!src_blkaddr)
			return -ENOMEM;

		do_replace = f2fs_kvzalloc(F2FS_I_SB(src_inode),
					array_size(olen, sizeof(int)),
					GFP_KERNEL);
		if (!do_replace) {
			kvfree(src_blkaddr);
			return -ENOMEM;
		}

		ret = __read_out_blkaddrs(src_inode, src_blkaddr,
					do_replace, src, olen);
		if (ret)
			goto roll_back;

		ret = __clone_blkaddrs(src_inode, dst_inode, src_blkaddr,
					do_replace, src, dst, olen, full);
		if (ret)
			goto roll_back;

		src += olen;
		dst += olen;
		len -= olen;

		kvfree(src_blkaddr);
		kvfree(do_replace);
	}
	return 0;

roll_back:
	__roll_back_blkaddrs(src_inode, src_blkaddr, do_replace, src, olen);
	kvfree(src_blkaddr);
	kvfree(do_replace);
	return ret;
}