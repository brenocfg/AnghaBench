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

/* Variables and functions */
 int MAX_BAUD_RATE ; 

__attribute__((used)) static inline int calc_baud_divisor(int baudrate)
{
	int divisor, rem;

	divisor = MAX_BAUD_RATE / baudrate;
	rem = MAX_BAUD_RATE % baudrate;
	/* Round to nearest divisor */
	if (((rem * 2) >= baudrate) && (baudrate != 110))
		divisor++;

	return divisor;
}