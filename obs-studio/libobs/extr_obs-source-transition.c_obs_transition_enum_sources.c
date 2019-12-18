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
struct TYPE_7__ {scalar_t__* transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  int /*<<< orphan*/  (* obs_source_enum_proc_t ) (TYPE_1__*,scalar_t__,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  lock_transition (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_transition (TYPE_1__*) ; 

void obs_transition_enum_sources(obs_source_t *transition,
				 obs_source_enum_proc_t cb, void *param)
{
	lock_transition(transition);
	for (size_t i = 0; i < 2; i++) {
		if (transition->transition_sources[i])
			cb(transition, transition->transition_sources[i],
			   param);
	}
	unlock_transition(transition);
}