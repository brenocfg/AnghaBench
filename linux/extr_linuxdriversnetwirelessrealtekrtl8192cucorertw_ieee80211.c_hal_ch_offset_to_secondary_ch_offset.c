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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_UPPER ; 
 scalar_t__ SCA ; 
 scalar_t__ SCB ; 
 scalar_t__ SCN ; 

inline u8 hal_ch_offset_to_secondary_ch_offset(u8 ch_offset)
{
	if (ch_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)
		return SCN;
	else if(ch_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
		return SCB;
	else if(ch_offset == HAL_PRIME_CHNL_OFFSET_UPPER)
		return SCA;

	return SCN;
}