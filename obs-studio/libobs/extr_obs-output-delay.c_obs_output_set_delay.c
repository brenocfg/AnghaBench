#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_8__ {void* delay_flags; void* delay_sec; TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int OBS_OUTPUT_ENCODED ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_3__*,char*) ; 

void obs_output_set_delay(obs_output_t *output, uint32_t delay_sec,
			  uint32_t flags)
{
	if (!obs_output_valid(output, "obs_output_set_delay"))
		return;

	if ((output->info.flags & OBS_OUTPUT_ENCODED) == 0) {
		blog(LOG_WARNING,
		     "Output '%s': Tried to set a delay "
		     "value on a non-encoded output",
		     output->context.name);
		return;
	}

	output->delay_sec = delay_sec;
	output->delay_flags = flags;
}