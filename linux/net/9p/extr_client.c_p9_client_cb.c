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
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;
struct p9_req_t {int status; TYPE_1__ tc; int /*<<< orphan*/  wq; } ;
struct p9_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_req_put (struct p9_req_t*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void p9_client_cb(struct p9_client *c, struct p9_req_t *req, int status)
{
	p9_debug(P9_DEBUG_MUX, " tag %d\n", req->tc.tag);

	/*
	 * This barrier is needed to make sure any change made to req before
	 * the status change is visible to another thread
	 */
	smp_wmb();
	req->status = status;

	wake_up(&req->wq);
	p9_debug(P9_DEBUG_MUX, "wakeup: %d\n", req->tc.tag);
	p9_req_put(req);
}