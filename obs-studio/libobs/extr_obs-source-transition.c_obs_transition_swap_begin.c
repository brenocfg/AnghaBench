#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/ * copy_source_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lock_textures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_transition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_transition (int /*<<< orphan*/ *) ; 

void obs_transition_swap_begin(obs_source_t *tr_dest, obs_source_t *tr_source)
{
	obs_source_t *old_children[2];

	if (tr_dest == tr_source)
		return;

	lock_textures(tr_source);
	lock_textures(tr_dest);

	lock_transition(tr_source);
	lock_transition(tr_dest);

	for (size_t i = 0; i < 2; i++)
		old_children[i] = copy_source_state(tr_dest, tr_source, i);

	unlock_transition(tr_dest);
	unlock_transition(tr_source);

	for (size_t i = 0; i < 2; i++)
		obs_source_release(old_children[i]);
}