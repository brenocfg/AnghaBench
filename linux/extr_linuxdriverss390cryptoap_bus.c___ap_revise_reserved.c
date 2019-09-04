#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  aqm; int /*<<< orphan*/  apm; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_DBF (int /*<<< orphan*/ ,char*,int,int) ; 
 int AP_DRIVER_FLAG_DEFAULT ; 
 int AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_DEBUG ; 
 TYPE_3__ ap_perms ; 
 int /*<<< orphan*/  ap_perms_mutex ; 
 int device_reprobe (struct device*) ; 
 scalar_t__ is_queue_dev (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit_inv (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_ap_drv (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_ap_queue (struct device*) ; 

__attribute__((used)) static int __ap_revise_reserved(struct device *dev, void *dummy)
{
	int rc, card, queue, devres, drvres;

	if (is_queue_dev(dev)) {
		card = AP_QID_CARD(to_ap_queue(dev)->qid);
		queue = AP_QID_QUEUE(to_ap_queue(dev)->qid);
		mutex_lock(&ap_perms_mutex);
		devres = test_bit_inv(card, ap_perms.apm)
			&& test_bit_inv(queue, ap_perms.aqm);
		mutex_unlock(&ap_perms_mutex);
		drvres = to_ap_drv(dev->driver)->flags
			& AP_DRIVER_FLAG_DEFAULT;
		if (!!devres != !!drvres) {
			AP_DBF(DBF_DEBUG, "reprobing queue=%02x.%04x\n",
			       card, queue);
			rc = device_reprobe(dev);
		}
	}

	return 0;
}