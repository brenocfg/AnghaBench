#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_queue {int online; int /*<<< orphan*/  list; TYPE_4__* queue; TYPE_2__* ops; struct zcrypt_card* zcard; } ;
struct zcrypt_card {int /*<<< orphan*/  zqueues; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_5__ device; } ;
struct TYPE_10__ {TYPE_3__ ap_dev; int /*<<< orphan*/  qid; TYPE_1__* card; } ;
struct TYPE_8__ {scalar_t__ rng; } ;
struct TYPE_7__ {struct zcrypt_card* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (TYPE_5__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_card_get (struct zcrypt_card*) ; 
 int /*<<< orphan*/  zcrypt_card_put (struct zcrypt_card*) ; 
 int /*<<< orphan*/  zcrypt_device_count ; 
 int /*<<< orphan*/  zcrypt_list_lock ; 
 int /*<<< orphan*/  zcrypt_queue_attr_group ; 
 int zcrypt_rng_device_add () ; 

int zcrypt_queue_register(struct zcrypt_queue *zq)
{
	struct zcrypt_card *zc;
	int rc;

	spin_lock(&zcrypt_list_lock);
	zc = zq->queue->card->private;
	zcrypt_card_get(zc);
	zq->zcard = zc;
	zq->online = 1;	/* New devices are online by default. */

	ZCRYPT_DBF(DBF_INFO, "queue=%02x.%04x register online=1\n",
		   AP_QID_CARD(zq->queue->qid), AP_QID_QUEUE(zq->queue->qid));

	list_add_tail(&zq->list, &zc->zqueues);
	zcrypt_device_count++;
	spin_unlock(&zcrypt_list_lock);

	rc = sysfs_create_group(&zq->queue->ap_dev.device.kobj,
				&zcrypt_queue_attr_group);
	if (rc)
		goto out;
	get_device(&zq->queue->ap_dev.device);

	if (zq->ops->rng) {
		rc = zcrypt_rng_device_add();
		if (rc)
			goto out_unregister;
	}
	return 0;

out_unregister:
	sysfs_remove_group(&zq->queue->ap_dev.device.kobj,
			   &zcrypt_queue_attr_group);
	put_device(&zq->queue->ap_dev.device);
out:
	spin_lock(&zcrypt_list_lock);
	list_del_init(&zq->list);
	spin_unlock(&zcrypt_list_lock);
	zcrypt_card_put(zc);
	return rc;
}