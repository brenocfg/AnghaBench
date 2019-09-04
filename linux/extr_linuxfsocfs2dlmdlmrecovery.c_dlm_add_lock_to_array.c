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
struct dlm_migratable_lockres {int num_locks; struct dlm_migratable_lock* ml; } ;
struct dlm_migratable_lock {int list; int /*<<< orphan*/  node; int /*<<< orphan*/  flags; int /*<<< orphan*/  highest_blocked; int /*<<< orphan*/  convert_type; int /*<<< orphan*/  type; int /*<<< orphan*/  cookie; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; int /*<<< orphan*/  highest_blocked; int /*<<< orphan*/  convert_type; int /*<<< orphan*/  type; int /*<<< orphan*/  cookie; } ;
struct dlm_lock {TYPE_2__ ml; TYPE_1__* lksb; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int DLM_MAX_MIGRATABLE_LOCKS ; 
 int /*<<< orphan*/  dlm_prepare_lvb_for_migration (struct dlm_lock*,struct dlm_migratable_lockres*,int) ; 

__attribute__((used)) static int dlm_add_lock_to_array(struct dlm_lock *lock,
				 struct dlm_migratable_lockres *mres, int queue)
{
	struct dlm_migratable_lock *ml;
	int lock_num = mres->num_locks;

	ml = &(mres->ml[lock_num]);
	ml->cookie = lock->ml.cookie;
	ml->type = lock->ml.type;
	ml->convert_type = lock->ml.convert_type;
	ml->highest_blocked = lock->ml.highest_blocked;
	ml->list = queue;
	if (lock->lksb) {
		ml->flags = lock->lksb->flags;
		dlm_prepare_lvb_for_migration(lock, mres, queue);
	}
	ml->node = lock->ml.node;
	mres->num_locks++;
	/* we reached the max, send this network message */
	if (mres->num_locks == DLM_MAX_MIGRATABLE_LOCKS)
		return 1;
	return 0;
}