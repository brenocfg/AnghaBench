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
typedef  int s8 ;
typedef  int s16 ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static s16 odm_cfo(s8 value)
{
	s16 ret_val;

	if (value < 0) {
		ret_val = 0 - value;
		ret_val = (ret_val << 1) + (ret_val >> 1); /* *2.5~=312.5/2^7 */
		ret_val =
			ret_val | BIT(12); /* set bit12 as 1 for negative cfo */
	} else {
		ret_val = value;
		ret_val = (ret_val << 1) + (ret_val >> 1); /* *2.5~=312.5/2^7 */
	}
	return ret_val;
}