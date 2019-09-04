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

__attribute__((used)) static int rtl8xxxu_gen1_channel_to_group(int channel)
{
	int group;

	if (channel < 4)
		group = 0;
	else if (channel < 10)
		group = 1;
	else
		group = 2;

	return group;
}