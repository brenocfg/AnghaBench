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
struct rsnd_dai {int max_channels; } ;

/* Variables and functions */

int rsnd_rdai_channels_ctrl(struct rsnd_dai *rdai,
			    int max_channels)
{
	if (max_channels > 0)
		rdai->max_channels = max_channels;

	return rdai->max_channels;
}