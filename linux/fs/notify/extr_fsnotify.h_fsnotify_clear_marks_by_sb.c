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
struct super_block {int /*<<< orphan*/  s_fsnotify_marks; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsnotify_destroy_marks (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fsnotify_clear_marks_by_sb(struct super_block *sb)
{
	fsnotify_destroy_marks(&sb->s_fsnotify_marks);
}