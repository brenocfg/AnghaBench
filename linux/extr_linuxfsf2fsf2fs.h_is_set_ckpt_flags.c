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

/* Variables and functions */
 int /*<<< orphan*/  F2FS_CKPT (struct f2fs_sb_info*) ; 
 int __is_set_ckpt_flags (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline bool is_set_ckpt_flags(struct f2fs_sb_info *sbi, unsigned int f)
{
	return __is_set_ckpt_flags(F2FS_CKPT(sbi), f);
}