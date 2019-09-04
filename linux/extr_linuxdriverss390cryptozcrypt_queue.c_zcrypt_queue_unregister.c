#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_queue {TYPE_3__* queue; TYPE_1__* ops; int /*<<< orphan*/  list; struct zcrypt_card* zcard; } ;
struct zcrypt_card {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_4__ device; } ;
struct TYPE_7__ {TYPE_2__ ap_dev; int /*<<< orphan*/  qid; } ;
struct TYPE_5__ {scalar_t__ rng; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_card_put (struct zcrypt_card*) ; 
 int /*<<< orphan*/  zcrypt_device_count ; 
 int /*<<< orphan*/  zcrypt_list_lock ; 
 int /*<<< orphan*/  zcrypt_queue_attr_group ; 
 int /*<<< orphan*/  zcrypt_queue_put (struct zcrypt_queue*) ; 
 int /*<<< orphan*/  zcrypt_rng_device_remove () ; 

void zcrypt_queue_unregister(struct zcrypt_queue *zq)
{
	struct zcrypt_card *zc;

	ZCRYPT_DBF(DBF_INFO, "queue=%02x.%04x unregister\n",
		   AP_QID_CARD(zq->queue->qid), AP_QID_QUEUE(zq->queue->qid));

	zc = zq->zcard;
	spin_lock(&zcrypt_list_lock);
	list_del_init(&zq->list);
	zcrypt_device_count--;
	spin_unlock(&zcrypt_list_lock);
	zcrypt_card_put(zc);
	if (zq->ops->rng)
		zcrypt_rng_device_remove();
	sysfs_remove_group(&zq->queue->ap_dev.device.kobj,
			   &zcrypt_queue_attr_group);
	put_device(&zq->queue->ap_dev.device);
	zcrypt_queue_put(zq);
}