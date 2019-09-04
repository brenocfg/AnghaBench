#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs4_state {int /*<<< orphan*/  inode; int /*<<< orphan*/  const open_stateid; int /*<<< orphan*/  const stateid; int /*<<< orphan*/  flags; int /*<<< orphan*/  seqlock; TYPE_1__* owner; int /*<<< orphan*/  waitq; } ;
typedef  int /*<<< orphan*/  const nfs4_stateid ;
struct TYPE_4__ {int /*<<< orphan*/  nfs_client; } ;
struct TYPE_3__ {int /*<<< orphan*/  so_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINTR ; 
 int HZ ; 
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 int /*<<< orphan*/  NFS_OPEN_STATE ; 
 TYPE_2__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_STATE_CHANGE_WAIT ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_has_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs4_stateid_match_other (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs_need_update_open_stateid (struct nfs4_state*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs_state_log_update_open_stateid (struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs_test_and_clear_all_open_stateid (struct nfs4_state*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ schedule_timeout (int) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs4_open_stateid_update (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  trace_nfs4_open_stateid_update_wait (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_set_open_stateid_locked(struct nfs4_state *state,
		const nfs4_stateid *stateid, nfs4_stateid *freeme)
{
	DEFINE_WAIT(wait);
	int status = 0;
	for (;;) {

		if (!nfs_need_update_open_stateid(state, stateid))
			return;
		if (!test_bit(NFS_STATE_CHANGE_WAIT, &state->flags))
			break;
		if (status)
			break;
		/* Rely on seqids for serialisation with NFSv4.0 */
		if (!nfs4_has_session(NFS_SERVER(state->inode)->nfs_client))
			break;

		prepare_to_wait(&state->waitq, &wait, TASK_KILLABLE);
		/*
		 * Ensure we process the state changes in the same order
		 * in which the server processed them by delaying the
		 * update of the stateid until we are in sequence.
		 */
		write_sequnlock(&state->seqlock);
		spin_unlock(&state->owner->so_lock);
		rcu_read_unlock();
		trace_nfs4_open_stateid_update_wait(state->inode, stateid, 0);
		if (!signal_pending(current)) {
			if (schedule_timeout(5*HZ) == 0)
				status = -EAGAIN;
			else
				status = 0;
		} else
			status = -EINTR;
		finish_wait(&state->waitq, &wait);
		rcu_read_lock();
		spin_lock(&state->owner->so_lock);
		write_seqlock(&state->seqlock);
	}

	if (test_bit(NFS_OPEN_STATE, &state->flags) &&
	    !nfs4_stateid_match_other(stateid, &state->open_stateid)) {
		nfs4_stateid_copy(freeme, &state->open_stateid);
		nfs_test_and_clear_all_open_stateid(state);
	}

	if (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0)
		nfs4_stateid_copy(&state->stateid, stateid);
	nfs4_stateid_copy(&state->open_stateid, stateid);
	trace_nfs4_open_stateid_update(state->inode, stateid, status);
	nfs_state_log_update_open_stateid(state);
}