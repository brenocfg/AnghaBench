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
struct raw3270_request {scalar_t__ rc; scalar_t__ rescnt; scalar_t__ view; } ;
struct fs3270 {scalar_t__ rdbuf_size; int /*<<< orphan*/  wait; TYPE_1__* rdbuf; scalar_t__ fs_pid; } ;
struct TYPE_2__ {int* data; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  kill_pid (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw3270_request_reset (struct raw3270_request*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fs3270_save_callback(struct raw3270_request *rq, void *data)
{
	struct fs3270 *fp;

	fp = (struct fs3270 *) rq->view;

	/* Correct idal buffer element 0 address. */
	fp->rdbuf->data[0] -= 5;
	fp->rdbuf->size += 5;

	/*
	 * If the rdbuf command failed or the idal buffer is
	 * to small for the amount of data returned by the
	 * rdbuf command, then we have no choice but to send
	 * a SIGHUP to the application.
	 */
	if (rq->rc != 0 || rq->rescnt == 0) {
		if (fp->fs_pid)
			kill_pid(fp->fs_pid, SIGHUP, 1);
		fp->rdbuf_size = 0;
	} else
		fp->rdbuf_size = fp->rdbuf->size - rq->rescnt;
	raw3270_request_reset(rq);
	wake_up(&fp->wait);
}