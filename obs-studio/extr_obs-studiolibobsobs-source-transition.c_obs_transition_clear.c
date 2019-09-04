#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* transition_source_active; int transitioning_video; int transitioning_audio; struct TYPE_9__** transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  lock_transition (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_release (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_remove_active_child (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  transition_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  unlock_transition (TYPE_1__*) ; 

void obs_transition_clear(obs_source_t *transition)
{
	obs_source_t *s[2];
	bool active[2];

	if (!transition_valid(transition, "obs_transition_clear"))
		return;

	lock_transition(transition);
	for (size_t i = 0; i < 2; i++) {
		s[i] = transition->transition_sources[i];
		active[i] = transition->transition_source_active[i];
		transition->transition_sources[i] = NULL;
		transition->transition_source_active[i] = false;
	}
	transition->transitioning_video = false;
	transition->transitioning_audio = false;
	unlock_transition(transition);

	for (size_t i = 0; i < 2; i++) {
		if (s[i] && active[i])
			obs_source_remove_active_child(transition, s[i]);
		obs_source_release(s[i]);
	}
}