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
struct TYPE_7__ {int /*<<< orphan*/ * transition_texrender; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_texrender_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalculate_transition_matrices (TYPE_1__*) ; 
 int /*<<< orphan*/  recalculate_transition_size (TYPE_1__*) ; 
 scalar_t__ trylock_textures (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_textures (TYPE_1__*) ; 

void obs_transition_tick(obs_source_t *transition)
{
	recalculate_transition_size(transition);
	recalculate_transition_matrices(transition);

	if (trylock_textures(transition) == 0) {
		gs_texrender_reset(transition->transition_texrender[0]);
		gs_texrender_reset(transition->transition_texrender[1]);
		unlock_textures(transition);
	}
}