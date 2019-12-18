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
struct TYPE_6__ {int* transition_source_active; struct TYPE_6__** transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_release (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_remove_active_child (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void obs_transition_stop(obs_source_t *transition)
{
	obs_source_t *old_child = transition->transition_sources[0];

	if (old_child && transition->transition_source_active[0])
		obs_source_remove_active_child(transition, old_child);
	obs_source_release(old_child);

	transition->transition_source_active[0] = true;
	transition->transition_source_active[1] = false;
	transition->transition_sources[0] = transition->transition_sources[1];
	transition->transition_sources[1] = NULL;
}