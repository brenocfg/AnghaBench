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
struct nfs4_state {int /*<<< orphan*/  waitq; int /*<<< orphan*/  seqlock; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  lock_states; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct nfs4_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_state *
nfs4_alloc_open_state(void)
{
	struct nfs4_state *state;

	state = kzalloc(sizeof(*state), GFP_NOFS);
	if (!state)
		return NULL;
	refcount_set(&state->count, 1);
	INIT_LIST_HEAD(&state->lock_states);
	spin_lock_init(&state->state_lock);
	seqlock_init(&state->seqlock);
	init_waitqueue_head(&state->waitq);
	return state;
}