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
typedef  enum wbus { ____Placeholder_wbus } wbus ;

/* Variables and functions */
 int bus_2byte ; 
 int /*<<< orphan*/  byte0_out (unsigned char) ; 
 int /*<<< orphan*/  byte1_out (unsigned char) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  xl_shift_cclk (int) ; 

void xl_shift_bytes_out(enum wbus bus_byte, unsigned char *pdata)
{
	/*
	 * supports 1 and 2 bytes programming mode
	 */
	if (likely(bus_byte == bus_2byte))
		byte0_out(pdata[0]);

	byte1_out(pdata[1]);
	xl_shift_cclk(1);
}