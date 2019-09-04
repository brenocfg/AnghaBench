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
struct rsnd_dai {int ssi_lane; } ;

/* Variables and functions */

int rsnd_rdai_ssi_lane_ctrl(struct rsnd_dai *rdai,
			    int ssi_lane)
{
	if (ssi_lane > 0)
		rdai->ssi_lane = ssi_lane;

	return rdai->ssi_lane;
}