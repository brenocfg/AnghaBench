#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int transition_use_fixed_duration; int /*<<< orphan*/  transition_fixed_duration; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  transition_valid (TYPE_1__*,char*) ; 

void obs_transition_enable_fixed(obs_source_t *transition, bool enable,
				 uint32_t duration)
{
	if (!transition_valid(transition, "obs_transition_enable_fixed"))
		return;

	transition->transition_use_fixed_duration = enable;
	transition->transition_fixed_duration = duration;
}