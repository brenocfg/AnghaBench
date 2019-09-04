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

int
zoran_proc_init (struct zoran *zr)
{
#ifdef CONFIG_PROC_FS
	char name[8];

	snprintf(name, 7, "zoran%d", zr->id);
	zr->zoran_proc = proc_create_data(name, 0, NULL, &zoran_operations, zr);
	if (zr->zoran_proc != NULL) {
		dprintk(2,
			KERN_INFO
			"%s: procfs entry /proc/%s allocated. data=%p\n",
			ZR_DEVNAME(zr), name, zr);
	} else {
		dprintk(1, KERN_ERR "%s: Unable to initialise /proc/%s\n",
			ZR_DEVNAME(zr), name);
		return 1;
	}
#endif
	return 0;
}