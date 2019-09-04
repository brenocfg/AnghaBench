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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ DWC_HFNUM_MAX_FRNUM ; 

__attribute__((used)) static inline int dwc_frame_num_gt(uint16_t frame1, uint16_t frame2)
{
	return (frame1 != frame2) &&
	    (((frame1 - frame2) & DWC_HFNUM_MAX_FRNUM) <
	     (DWC_HFNUM_MAX_FRNUM >> 1));
}