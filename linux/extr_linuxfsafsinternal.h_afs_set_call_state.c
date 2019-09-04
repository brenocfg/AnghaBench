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
struct afs_call {int state; int /*<<< orphan*/  state_lock; } ;
typedef  enum afs_call_state { ____Placeholder_afs_call_state } afs_call_state ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_call_state (struct afs_call*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool afs_set_call_state(struct afs_call *call,
				      enum afs_call_state from,
				      enum afs_call_state to)
{
	bool ok = false;

	spin_lock_bh(&call->state_lock);
	if (call->state == from) {
		call->state = to;
		trace_afs_call_state(call, from, to, 0, 0);
		ok = true;
	}
	spin_unlock_bh(&call->state_lock);
	return ok;
}