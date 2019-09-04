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
 scalar_t__ const GSM1_ESCAPE ; 
 int GSM1_ESCAPE_BITS ; 
 scalar_t__ const GSM1_SOF ; 
 scalar_t__ const XOFF ; 
 scalar_t__ const XON ; 

__attribute__((used)) static int gsm_stuff_frame(const u8 *input, u8 *output, int len)
{
	int olen = 0;
	while (len--) {
		if (*input == GSM1_SOF || *input == GSM1_ESCAPE
		    || *input == XON || *input == XOFF) {
			*output++ = GSM1_ESCAPE;
			*output++ = *input++ ^ GSM1_ESCAPE_BITS;
			olen++;
		} else
			*output++ = *input++;
		olen++;
	}
	return olen;
}