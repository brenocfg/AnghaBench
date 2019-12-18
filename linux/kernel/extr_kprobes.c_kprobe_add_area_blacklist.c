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

/* Variables and functions */
 int kprobe_add_ksym_blacklist (unsigned long) ; 

int kprobe_add_area_blacklist(unsigned long start, unsigned long end)
{
	unsigned long entry;
	int ret = 0;

	for (entry = start; entry < end; entry += ret) {
		ret = kprobe_add_ksym_blacklist(entry);
		if (ret < 0)
			return ret;
		if (ret == 0)	/* In case of alias symbol */
			ret = 1;
	}
	return 0;
}