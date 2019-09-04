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
 int READBACK_ADD_HALF ; 
 int READBACK_NEGATE ; 
 int READBACK_VALUE_MASK ; 
 int READBACK_VALUE_SHIFT ; 

__attribute__((used)) static int translate_temp(u16 val)
{
	int t;

	t = ((val & READBACK_VALUE_MASK) >> READBACK_VALUE_SHIFT) * 1000;
	if (val & READBACK_ADD_HALF)
		t += 500;
	if (val & READBACK_NEGATE)
		t *= -1;

	return t;
}