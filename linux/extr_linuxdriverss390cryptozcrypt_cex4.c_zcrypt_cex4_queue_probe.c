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
struct zcrypt_queue {int online; int /*<<< orphan*/  reply; int /*<<< orphan*/  load; struct ap_queue* queue; void* ops; } ;
struct ap_queue {struct zcrypt_queue* private; int /*<<< orphan*/  request_timeout; TYPE_1__* card; } ;
struct ap_device {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  functions; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_FUNC_ACCEL ; 
 int /*<<< orphan*/  AP_FUNC_COPRO ; 
 int /*<<< orphan*/  AP_FUNC_EP11 ; 
 int /*<<< orphan*/  CEX4A_MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  CEX4C_MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  CEX4_CLEANUP_TIME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MSGTYPE06_NAME ; 
 int /*<<< orphan*/  MSGTYPE06_VARIANT_DEFAULT ; 
 int /*<<< orphan*/  MSGTYPE06_VARIANT_EP11 ; 
 int /*<<< orphan*/  MSGTYPE50_NAME ; 
 int /*<<< orphan*/  MSGTYPE50_VARIANT_DEFAULT ; 
 int /*<<< orphan*/  ap_queue_init_reply (struct ap_queue*,int /*<<< orphan*/ *) ; 
 scalar_t__ ap_test_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ap_queue* to_ap_queue (int /*<<< orphan*/ *) ; 
 void* zcrypt_msgtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zcrypt_queue* zcrypt_queue_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_queue_free (struct zcrypt_queue*) ; 
 int zcrypt_queue_register (struct zcrypt_queue*) ; 

__attribute__((used)) static int zcrypt_cex4_queue_probe(struct ap_device *ap_dev)
{
	struct ap_queue *aq = to_ap_queue(&ap_dev->device);
	struct zcrypt_queue *zq;
	int rc;

	if (ap_test_bit(&aq->card->functions, AP_FUNC_ACCEL)) {
		zq = zcrypt_queue_alloc(CEX4A_MAX_MESSAGE_SIZE);
		if (!zq)
			return -ENOMEM;
		zq->ops = zcrypt_msgtype(MSGTYPE50_NAME,
					 MSGTYPE50_VARIANT_DEFAULT);
	} else if (ap_test_bit(&aq->card->functions, AP_FUNC_COPRO)) {
		zq = zcrypt_queue_alloc(CEX4C_MAX_MESSAGE_SIZE);
		if (!zq)
			return -ENOMEM;
		zq->ops = zcrypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VARIANT_DEFAULT);
	} else if (ap_test_bit(&aq->card->functions, AP_FUNC_EP11)) {
		zq = zcrypt_queue_alloc(CEX4C_MAX_MESSAGE_SIZE);
		if (!zq)
			return -ENOMEM;
		zq->ops = zcrypt_msgtype(MSGTYPE06_NAME,
					 MSGTYPE06_VARIANT_EP11);
	} else {
		return -ENODEV;
	}
	zq->queue = aq;
	zq->online = 1;
	atomic_set(&zq->load, 0);
	ap_queue_init_reply(aq, &zq->reply);
	aq->request_timeout = CEX4_CLEANUP_TIME,
	aq->private = zq;
	rc = zcrypt_queue_register(zq);
	if (rc) {
		aq->private = NULL;
		zcrypt_queue_free(zq);
	}

	return rc;
}