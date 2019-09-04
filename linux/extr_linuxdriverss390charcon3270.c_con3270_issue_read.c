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
struct raw3270_request {struct con3270* callback_data; int /*<<< orphan*/  callback; } ;
struct con3270 {int /*<<< orphan*/  view; TYPE_1__* input; int /*<<< orphan*/  read; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_READMOD ; 
 int /*<<< orphan*/  con3270_read_callback ; 
 int /*<<< orphan*/  raw3270_request_reset (struct raw3270_request*) ; 
 int /*<<< orphan*/  raw3270_request_set_cmd (struct raw3270_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_request_set_data (struct raw3270_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int raw3270_start_irq (int /*<<< orphan*/ *,struct raw3270_request*) ; 
 struct raw3270_request* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
con3270_issue_read(struct con3270 *cp)
{
	struct raw3270_request *rrq;
	int rc;

	rrq = xchg(&cp->read, 0);
	if (!rrq)
		/* Read already scheduled. */
		return;
	rrq->callback = con3270_read_callback;
	rrq->callback_data = cp;
	raw3270_request_set_cmd(rrq, TC_READMOD);
	raw3270_request_set_data(rrq, cp->input->string, cp->input->len);
	/* Issue the read modified request. */
	rc = raw3270_start_irq(&cp->view, rrq);
	if (rc)
		raw3270_request_reset(rrq);
}