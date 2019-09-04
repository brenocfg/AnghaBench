#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ stop_code; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_output_signal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  obs_output_actual_stop (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stopping (TYPE_1__*) ; 

void obs_output_force_stop(obs_output_t *output)
{
	if (!obs_output_valid(output, "obs_output_force_stop"))
		return;

	if (!stopping(output)) {
		output->stop_code = 0;
		do_output_signal(output, "stopping");
	}
	obs_output_actual_stop(output, true, 0);
}