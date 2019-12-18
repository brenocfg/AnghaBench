#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__** transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum obs_transition_target { ____Placeholder_obs_transition_target } obs_transition_target ;

/* Variables and functions */
 int /*<<< orphan*/  lock_transition (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_addref (TYPE_1__*) ; 
 int /*<<< orphan*/  transition_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  unlock_transition (TYPE_1__*) ; 

obs_source_t *obs_transition_get_source(obs_source_t *transition,
					enum obs_transition_target target)
{
	size_t idx = (size_t)target;
	obs_source_t *ret;

	if (!transition_valid(transition, "obs_transition_get_source"))
		return NULL;

	lock_transition(transition);
	ret = transition->transition_sources[idx];
	obs_source_addref(ret);
	unlock_transition(transition);

	return ret;
}