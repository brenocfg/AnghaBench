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
struct f2fs_io_info {int /*<<< orphan*/  new_blkaddr; int /*<<< orphan*/  old_blkaddr; struct f2fs_sb_info* sbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_GENERIC ; 
 int /*<<< orphan*/  DATA_GENERIC_ENHANCE ; 
 int /*<<< orphan*/  META_GENERIC ; 
 scalar_t__ __is_meta_io (struct f2fs_io_info*) ; 
 scalar_t__ __is_valid_data_blkaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_blkaddr (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void verify_fio_blkaddr(struct f2fs_io_info *fio)
{
	struct f2fs_sb_info *sbi = fio->sbi;

	if (__is_valid_data_blkaddr(fio->old_blkaddr))
		verify_blkaddr(sbi, fio->old_blkaddr, __is_meta_io(fio) ?
					META_GENERIC : DATA_GENERIC);
	verify_blkaddr(sbi, fio->new_blkaddr, __is_meta_io(fio) ?
					META_GENERIC : DATA_GENERIC_ENHANCE);
}