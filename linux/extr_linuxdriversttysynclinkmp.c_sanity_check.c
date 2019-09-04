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
typedef  int /*<<< orphan*/  SLMP_INFO ;

/* Variables and functions */

__attribute__((used)) static inline int sanity_check(SLMP_INFO *info,
			       char *name, const char *routine)
{
#ifdef SANITY_CHECK
	static const char *badmagic =
		"Warning: bad magic number for synclinkmp_struct (%s) in %s\n";
	static const char *badinfo =
		"Warning: null synclinkmp_struct for (%s) in %s\n";

	if (!info) {
		printk(badinfo, name, routine);
		return 1;
	}
	if (info->magic != MGSL_MAGIC) {
		printk(badmagic, name, routine);
		return 1;
	}
#else
	if (!info)
		return 1;
#endif
	return 0;
}