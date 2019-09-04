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
struct super_block {scalar_t__ s_magic; scalar_t__ s_fs_info; } ;
struct autofs_sb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTOFS_SUPER_MAGIC ; 

__attribute__((used)) static inline struct autofs_sb_info *autofs_sbi(struct super_block *sb)
{
	return sb->s_magic != AUTOFS_SUPER_MAGIC ?
		NULL : (struct autofs_sb_info *)(sb->s_fs_info);
}