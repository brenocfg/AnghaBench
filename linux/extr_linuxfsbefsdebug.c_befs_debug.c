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

void
befs_debug(const struct super_block *sb, const char *fmt, ...)
{
#ifdef CONFIG_BEFS_DEBUG

	struct va_format vaf;
	va_list args;

	va_start(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_debug("(%s): %pV\n", sb->s_id, &vaf);
	va_end(args);

#endif				//CONFIG_BEFS_DEBUG
}