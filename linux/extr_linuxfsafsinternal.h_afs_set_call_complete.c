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
typedef  int /*<<< orphan*/  u32 ;
struct afs_call {int state; int error; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  abort_code; } ;
typedef  enum afs_call_state { ____Placeholder_afs_call_state } afs_call_state ;

/* Variables and functions */
 int AFS_CALL_COMPLETE ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_call_done (struct afs_call*) ; 
 int /*<<< orphan*/  trace_afs_call_state (struct afs_call*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void afs_set_call_complete(struct afs_call *call,
					 int error, u32 remote_abort)
{
	enum afs_call_state state;
	bool ok = false;

	spin_lock_bh(&call->state_lock);
	state = call->state;
	if (state != AFS_CALL_COMPLETE) {
		call->abort_code = remote_abort;
		call->error = error;
		call->state = AFS_CALL_COMPLETE;
		trace_afs_call_state(call, state, AFS_CALL_COMPLETE,
				     error, remote_abort);
		ok = true;
	}
	spin_unlock_bh(&call->state_lock);
	if (ok)
		trace_afs_call_done(call);
}