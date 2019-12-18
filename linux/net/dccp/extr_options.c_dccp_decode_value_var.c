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

u64 dccp_decode_value_var(const u8 *bf, const u8 len)
{
	u64 value = 0;

	if (len >= DCCP_OPTVAL_MAXLEN)
		value += ((u64)*bf++) << 40;
	if (len > 4)
		value += ((u64)*bf++) << 32;
	if (len > 3)
		value += ((u64)*bf++) << 24;
	if (len > 2)
		value += ((u64)*bf++) << 16;
	if (len > 1)
		value += ((u64)*bf++) << 8;
	if (len > 0)
		value += *bf;

	return value;
}