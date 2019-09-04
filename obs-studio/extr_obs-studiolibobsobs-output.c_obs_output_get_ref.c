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
struct TYPE_5__ {int /*<<< orphan*/  control; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 TYPE_1__* obs_weak_output_get_output (int /*<<< orphan*/ ) ; 

obs_output_t *obs_output_get_ref(obs_output_t *output)
{
	if (!output)
		return NULL;

	return obs_weak_output_get_output(output->control);
}