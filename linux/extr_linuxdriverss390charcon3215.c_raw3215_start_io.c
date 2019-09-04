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
struct raw3215_req {int /*<<< orphan*/  ccws; } ;
struct raw3215_info {int flags; struct raw3215_req* queued_write; int /*<<< orphan*/  cdev; struct raw3215_req* queued_read; } ;

/* Variables and functions */
 int RAW3215_STOPPED ; 
 int RAW3215_THROTTLED ; 
 int RAW3215_WORKING ; 
 int ccw_device_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raw3215_start_io(struct raw3215_info *raw)
{
	struct raw3215_req *req;
	int res;

	req = raw->queued_read;
	if (req != NULL &&
	    !(raw->flags & (RAW3215_WORKING | RAW3215_THROTTLED))) {
		/* dequeue request */
		raw->queued_read = NULL;
		res = ccw_device_start(raw->cdev, req->ccws,
				       (unsigned long) req, 0, 0);
		if (res != 0) {
			/* do_IO failed, put request back to queue */
			raw->queued_read = req;
		} else {
			raw->flags |= RAW3215_WORKING;
		}
	}
	req = raw->queued_write;
	if (req != NULL &&
	    !(raw->flags & (RAW3215_WORKING | RAW3215_STOPPED))) {
		/* dequeue request */
		raw->queued_write = NULL;
		res = ccw_device_start(raw->cdev, req->ccws,
				       (unsigned long) req, 0, 0);
		if (res != 0) {
			/* do_IO failed, put request back to queue */
			raw->queued_write = req;
		} else {
			raw->flags |= RAW3215_WORKING;
		}
	}
}