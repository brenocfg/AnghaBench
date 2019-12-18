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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ transition_cy; scalar_t__ transition_cx; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  transition_valid (TYPE_1__ const*,char*) ; 

void obs_transition_get_size(const obs_source_t *transition, uint32_t *cx,
			     uint32_t *cy)
{
	if (!transition_valid(transition, "obs_transition_set_size")) {
		*cx = 0;
		*cy = 0;
		return;
	}

	*cx = transition->transition_cx;
	*cy = transition->transition_cy;
}