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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static int drop_transfer(uint32_t trgt_fr, uint32_t curr_fr, uint8_t frm_overrun)
{
	int retval = 0;
	if(!frm_overrun && curr_fr >= trgt_fr)
		retval = 1;
	else if (frm_overrun
		 && (curr_fr >= trgt_fr && ((curr_fr - trgt_fr) < 0x3FFF / 2)))
		retval = 1;
	return retval;
}