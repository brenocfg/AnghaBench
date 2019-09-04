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

void reiserfs_debug(struct super_block *s, int level, const char *fmt, ...)
{
#ifdef CONFIG_REISERFS_CHECK
	do_reiserfs_warning(fmt);
	if (s)
		printk(KERN_DEBUG "REISERFS debug (device %s): %s\n",
		       s->s_id, error_buf);
	else
		printk(KERN_DEBUG "REISERFS debug: %s\n", error_buf);
#endif
}