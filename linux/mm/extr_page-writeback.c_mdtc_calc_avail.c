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
struct dirty_throttle_control {unsigned long dirty; unsigned long avail; } ;

/* Variables and functions */
 struct dirty_throttle_control* mdtc_gdtc (struct dirty_throttle_control*) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static void mdtc_calc_avail(struct dirty_throttle_control *mdtc,
			    unsigned long filepages, unsigned long headroom)
{
	struct dirty_throttle_control *gdtc = mdtc_gdtc(mdtc);
	unsigned long clean = filepages - min(filepages, mdtc->dirty);
	unsigned long global_clean = gdtc->avail - min(gdtc->avail, gdtc->dirty);
	unsigned long other_clean = global_clean - min(global_clean, clean);

	mdtc->avail = filepages + min(headroom, other_clean);
}