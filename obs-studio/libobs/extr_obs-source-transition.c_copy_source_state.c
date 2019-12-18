#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* transition_source_active; struct TYPE_10__** transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_add_active_child (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_addref (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_remove_active_child (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static inline obs_source_t *
copy_source_state(obs_source_t *tr_dest, obs_source_t *tr_source, size_t idx)
{
	obs_source_t *old_child = tr_dest->transition_sources[idx];
	obs_source_t *new_child = tr_source->transition_sources[idx];
	bool active = tr_source->transition_source_active[idx];

	if (old_child && tr_dest->transition_source_active[idx])
		obs_source_remove_active_child(tr_dest, old_child);

	tr_dest->transition_sources[idx] = new_child;
	tr_dest->transition_source_active[idx] = active;

	if (active && new_child)
		obs_source_add_active_child(tr_dest, new_child);
	obs_source_addref(new_child);

	return old_child;
}