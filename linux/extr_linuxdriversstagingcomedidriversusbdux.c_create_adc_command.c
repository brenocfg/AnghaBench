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

/* Variables and functions */

__attribute__((used)) static u8 create_adc_command(unsigned int chan, unsigned int range)
{
	u8 p = (range <= 1);
	u8 r = ((range % 2) == 0);

	return (chan << 4) | ((p == 1) << 2) | ((r == 1) << 3);
}