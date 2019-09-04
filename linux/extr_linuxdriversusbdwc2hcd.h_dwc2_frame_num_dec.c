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
typedef  int u16 ;

/* Variables and functions */
 int HFNUM_MAX_FRNUM ; 

__attribute__((used)) static inline u16 dwc2_frame_num_dec(u16 frame, u16 dec)
{
	return (frame + HFNUM_MAX_FRNUM + 1 - dec) & HFNUM_MAX_FRNUM;
}