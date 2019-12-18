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
struct rsnd_dai {int chan_width; } ;

/* Variables and functions */

int rsnd_rdai_width_ctrl(struct rsnd_dai *rdai, int width)
{
	if (width > 0)
		rdai->chan_width = width;

	return rdai->chan_width;
}