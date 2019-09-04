#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  inflight_assert_workers; TYPE_1__ lockname; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __dlm_lockres_grab_inflight_worker(struct dlm_ctxt *dlm,
		struct dlm_lock_resource *res)
{
	assert_spin_locked(&res->spinlock);
	res->inflight_assert_workers++;
	mlog(0, "%s:%.*s: inflight assert worker++: now %u\n",
			dlm->name, res->lockname.len, res->lockname.name,
			res->inflight_assert_workers);
}