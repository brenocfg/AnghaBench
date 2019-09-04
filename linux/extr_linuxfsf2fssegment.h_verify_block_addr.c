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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {struct f2fs_sb_info* sbi; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_GENERIC ; 
 int /*<<< orphan*/  META_GENERIC ; 
 scalar_t__ __is_meta_io (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  verify_blkaddr (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void verify_block_addr(struct f2fs_io_info *fio, block_t blk_addr)
{
	struct f2fs_sb_info *sbi = fio->sbi;

	if (__is_meta_io(fio))
		verify_blkaddr(sbi, blk_addr, META_GENERIC);
	else
		verify_blkaddr(sbi, blk_addr, DATA_GENERIC);
}