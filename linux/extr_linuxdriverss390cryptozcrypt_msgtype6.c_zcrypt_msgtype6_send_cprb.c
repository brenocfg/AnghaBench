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
struct zcrypt_queue {int /*<<< orphan*/  queue; } ;
struct response_type {int /*<<< orphan*/  work; } ;
struct ica_xcRB {int dummy; } ;
struct ap_message {int rc; scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_cancel_message (int /*<<< orphan*/ ,struct ap_message*) ; 
 int /*<<< orphan*/  ap_queue_message (int /*<<< orphan*/ ,struct ap_message*) ; 
 int convert_response_xcrb (struct zcrypt_queue*,struct ap_message*,struct ica_xcRB*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long zcrypt_msgtype6_send_cprb(struct zcrypt_queue *zq,
				    struct ica_xcRB *xcRB,
				    struct ap_message *ap_msg)
{
	int rc;
	struct response_type *rtype = (struct response_type *)(ap_msg->private);

	init_completion(&rtype->work);
	ap_queue_message(zq->queue, ap_msg);
	rc = wait_for_completion_interruptible(&rtype->work);
	if (rc == 0) {
		rc = ap_msg->rc;
		if (rc == 0)
			rc = convert_response_xcrb(zq, ap_msg, xcRB);
	} else
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);

	return rc;
}