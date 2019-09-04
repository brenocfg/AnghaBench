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
struct slgt_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int sanity_check(struct slgt_info *info, char *devname, const char *name)
{
#ifdef SANITY_CHECK
	if (!info) {
		printk("null struct slgt_info for (%s) in %s\n", devname, name);
		return 1;
	}
	if (info->magic != MGSL_MAGIC) {
		printk("bad magic number struct slgt_info (%s) in %s\n", devname, name);
		return 1;
	}
#else
	if (!info)
		return 1;
#endif
	return 0;
}