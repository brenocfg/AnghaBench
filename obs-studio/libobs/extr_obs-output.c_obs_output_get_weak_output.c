#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_weak_output_t ;
struct TYPE_3__ {int /*<<< orphan*/ * control; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_weak_output_addref (int /*<<< orphan*/ *) ; 

obs_weak_output_t *obs_output_get_weak_output(obs_output_t *output)
{
	if (!output)
		return NULL;

	obs_weak_output_t *weak = output->control;
	obs_weak_output_addref(weak);
	return weak;
}