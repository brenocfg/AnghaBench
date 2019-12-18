#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dac_channels_pcm; scalar_t__ update_center_lfe_mix; } ;
struct oxygen {TYPE_1__ model; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int upmix_item_count(struct oxygen *chip)
{
	if (chip->model.dac_channels_pcm < 8)
		return 2;
	else if (chip->model.update_center_lfe_mix)
		return 5;
	else
		return 3;
}