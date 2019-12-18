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
struct dlm_rsb {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKSTS_WAITING ; 
 int EAGAIN ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  add_lkb (struct dlm_rsb*,struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timeout (struct dlm_lkb*) ; 
 scalar_t__ can_be_granted (struct dlm_rsb*,struct dlm_lkb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ can_be_queued (struct dlm_lkb*) ; 
 int /*<<< orphan*/  grant_lock (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  queue_cast (struct dlm_rsb*,struct dlm_lkb*,int) ; 

__attribute__((used)) static int do_request(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int error = 0;

	if (can_be_granted(r, lkb, 1, 0, NULL)) {
		grant_lock(r, lkb);
		queue_cast(r, lkb, 0);
		goto out;
	}

	if (can_be_queued(lkb)) {
		error = -EINPROGRESS;
		add_lkb(r, lkb, DLM_LKSTS_WAITING);
		add_timeout(lkb);
		goto out;
	}

	error = -EAGAIN;
	queue_cast(r, lkb, -EAGAIN);
 out:
	return error;
}