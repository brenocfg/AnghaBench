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
struct zoran {int dummy; } ;

/* Variables and functions */

void
zoran_proc_cleanup (struct zoran *zr)
{
#ifdef CONFIG_PROC_FS
	char name[8];

	snprintf(name, 7, "zoran%d", zr->id);
	if (zr->zoran_proc)
		remove_proc_entry(name, NULL);
	zr->zoran_proc = NULL;
#endif
}