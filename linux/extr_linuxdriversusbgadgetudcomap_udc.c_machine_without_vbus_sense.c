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
 scalar_t__ cpu_is_omap7xx () ; 
 scalar_t__ machine_is_omap_innovator () ; 
 scalar_t__ machine_is_omap_osk () ; 
 scalar_t__ machine_is_omap_palmte () ; 
 scalar_t__ machine_is_sx1 () ; 

__attribute__((used)) static inline int machine_without_vbus_sense(void)
{
	return machine_is_omap_innovator()
		|| machine_is_omap_osk()
		|| machine_is_omap_palmte()
		|| machine_is_sx1()
		/* No known omap7xx boards with vbus sense */
		|| cpu_is_omap7xx();
}