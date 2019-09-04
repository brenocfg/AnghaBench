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
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __add_ino_entry (struct f2fs_sb_info*,int /*<<< orphan*/ ,unsigned int,int) ; 

void f2fs_set_dirty_device(struct f2fs_sb_info *sbi, nid_t ino,
					unsigned int devidx, int type)
{
	__add_ino_entry(sbi, ino, devidx, type);
}