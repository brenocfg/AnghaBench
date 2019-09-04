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
struct raw3270_view {int dummy; } ;
struct raw3270_request {int /*<<< orphan*/ * callback_data; int /*<<< orphan*/  callback; } ;
struct fs3270 {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  fs3270_wake_up ; 
 int /*<<< orphan*/  fs3270_working (struct fs3270*) ; 
 int /*<<< orphan*/  raw3270_request_final (struct raw3270_request*) ; 
 int raw3270_start (struct raw3270_view*,struct raw3270_request*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fs3270_do_io(struct raw3270_view *view, struct raw3270_request *rq)
{
	struct fs3270 *fp;
	int rc;

	fp = (struct fs3270 *) view;
	rq->callback = fs3270_wake_up;
	rq->callback_data = &fp->wait;

	do {
		if (!fs3270_working(fp)) {
			/* Fullscreen view isn't ready yet. */
			rc = wait_event_interruptible(fp->wait,
						      fs3270_working(fp));
			if (rc != 0)
				break;
		}
		rc = raw3270_start(view, rq);
		if (rc == 0) {
			/* Started successfully. Now wait for completion. */
			wait_event(fp->wait, raw3270_request_final(rq));
		}
	} while (rc == -EACCES);
	return rc;
}