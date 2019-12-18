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
struct spdif_mixer_control {int* ch_status; } ;

/* Variables and functions */

__attribute__((used)) static void spdif_set_cstatus(struct spdif_mixer_control *ctrl,
				u8 mask, u8 cstatus)
{
	ctrl->ch_status[3] &= ~mask;
	ctrl->ch_status[3] |= cstatus & mask;
}