#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* transition_source_active; scalar_t__* transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  lock_transition (TYPE_1__*) ; 
 int obs_source_add_active_child (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  unlock_transition (TYPE_1__*) ; 

__attribute__((used)) static inline bool activate_child(obs_source_t *transition, size_t idx)
{
	bool success = true;

	lock_transition(transition);

	if (transition->transition_sources[idx] &&
	    !transition->transition_source_active[idx]) {

		success = obs_source_add_active_child(
			transition, transition->transition_sources[idx]);
		if (success)
			transition->transition_source_active[idx] = true;
	}

	unlock_transition(transition);

	return success;
}