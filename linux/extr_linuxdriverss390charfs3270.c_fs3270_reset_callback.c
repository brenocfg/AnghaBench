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
struct raw3270_request {scalar_t__ view; } ;
struct fs3270 {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_request_reset (struct raw3270_request*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fs3270_reset_callback(struct raw3270_request *rq, void *data)
{
	struct fs3270 *fp;

	fp = (struct fs3270 *) rq->view;
	raw3270_request_reset(rq);
	wake_up(&fp->wait);
}