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
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_GENERIC ; 
 int /*<<< orphan*/  __is_valid_data_blkaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_blkaddr (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_valid_data_blkaddr(struct f2fs_sb_info *sbi,
						block_t blkaddr)
{
	if (!__is_valid_data_blkaddr(blkaddr))
		return false;
	verify_blkaddr(sbi, blkaddr, DATA_GENERIC);
	return true;
}