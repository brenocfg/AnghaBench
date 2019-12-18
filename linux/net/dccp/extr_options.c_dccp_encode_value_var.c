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
typedef  int u8 ;
typedef  int u64 ;

/* Variables and functions */
 int const DCCP_OPTVAL_MAXLEN ; 

void dccp_encode_value_var(const u64 value, u8 *to, const u8 len)
{
	if (len >= DCCP_OPTVAL_MAXLEN)
		*to++ = (value & 0xFF0000000000ull) >> 40;
	if (len > 4)
		*to++ = (value & 0xFF00000000ull) >> 32;
	if (len > 3)
		*to++ = (value & 0xFF000000) >> 24;
	if (len > 2)
		*to++ = (value & 0xFF0000) >> 16;
	if (len > 1)
		*to++ = (value & 0xFF00) >> 8;
	if (len > 0)
		*to++ = (value & 0xFF);
}