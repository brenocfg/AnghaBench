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
struct sis_video_info {int dummy; } ;

/* Variables and functions */

int sisfb_initaccel(struct sis_video_info *ivideo)
{
#ifdef SISFB_USE_SPINLOCKS
	spin_lock_init(&ivideo->lockaccel);
#endif
	return 0;
}