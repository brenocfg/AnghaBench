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
struct afs_call {int /*<<< orphan*/  work; TYPE_1__* type; } ;
struct TYPE_2__ {scalar_t__ work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  afs_call_trace_work ; 
 int /*<<< orphan*/  afs_get_call (struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_put_call (struct afs_call*) ; 
 int /*<<< orphan*/  afs_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_queue_call_work(struct afs_call *call)
{
	if (call->type->work) {
		INIT_WORK(&call->work, call->type->work);

		afs_get_call(call, afs_call_trace_work);
		if (!queue_work(afs_wq, &call->work))
			afs_put_call(call);
	}
}