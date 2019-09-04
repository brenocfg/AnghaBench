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

__attribute__((used)) static void create_adc_command(unsigned int chan,
			       u8 *muxsg0, u8 *muxsg1)
{
	if (chan < 8)
		(*muxsg0) = (*muxsg0) | (1 << chan);
	else if (chan < 16)
		(*muxsg1) = (*muxsg1) | (1 << (chan - 8));
}