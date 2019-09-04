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

__attribute__((used)) static inline int dscc4_check_clock_ability(int port)
{
	int ret = 0;

#ifdef CONFIG_DSCC4_PCISYNC
	if (port >= 2)
		ret = -1;
#endif
	return ret;
}