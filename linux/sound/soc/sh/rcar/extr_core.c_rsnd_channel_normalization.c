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

int rsnd_channel_normalization(int chan)
{
	if ((chan > 8) || (chan < 0))
		return 0;

	/* TDM Extend Mode needs 8ch */
	if (chan == 6)
		chan = 8;

	return chan;
}