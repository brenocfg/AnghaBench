#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct mxsfb_info {TYPE_1__* devdata; } ;
struct TYPE_2__ {unsigned int hs_wdth_mask; unsigned int hs_wdth_shift; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 set_hsync_pulse_width(struct mxsfb_info *host, unsigned val)
{
	return (val & host->devdata->hs_wdth_mask) <<
		host->devdata->hs_wdth_shift;
}