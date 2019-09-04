#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t mixer_mask; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  active (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_1__*,char*) ; 

void obs_output_set_mixer(obs_output_t *output, size_t mixer_idx)
{
	if (!obs_output_valid(output, "obs_output_set_mixer"))
		return;

	if (!active(output))
		output->mixer_mask = (size_t)1 << mixer_idx;
}