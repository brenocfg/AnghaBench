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
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsnotify_clear_marks_by_sb (struct super_block*) ; 
 int /*<<< orphan*/  fsnotify_unmount_inodes (struct super_block*) ; 

void fsnotify_sb_delete(struct super_block *sb)
{
	fsnotify_unmount_inodes(sb);
	fsnotify_clear_marks_by_sb(sb);
}