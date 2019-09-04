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

__attribute__((used)) static int usbduxsigma_chans_to_interval(int num_chan)
{
	if (num_chan <= 2)
		return 2;	/* 4kHz */
	if (num_chan <= 8)
		return 4;	/* 2kHz */
	return 8;		/* 1kHz */
}