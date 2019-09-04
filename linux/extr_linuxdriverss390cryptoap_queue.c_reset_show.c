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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ap_queue {int state; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  AP_STATE_QUEUE_FULL 131 
#define  AP_STATE_RESET_START 130 
#define  AP_STATE_RESET_WAIT 129 
#define  AP_STATE_WORKING 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_queue* to_ap_queue (struct device*) ; 

__attribute__((used)) static ssize_t reset_show(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct ap_queue *aq = to_ap_queue(dev);
	int rc = 0;

	spin_lock_bh(&aq->lock);
	switch (aq->state) {
	case AP_STATE_RESET_START:
	case AP_STATE_RESET_WAIT:
		rc = snprintf(buf, PAGE_SIZE, "Reset in progress.\n");
		break;
	case AP_STATE_WORKING:
	case AP_STATE_QUEUE_FULL:
		rc = snprintf(buf, PAGE_SIZE, "Reset Timer armed.\n");
		break;
	default:
		rc = snprintf(buf, PAGE_SIZE, "No Reset Timer set.\n");
	}
	spin_unlock_bh(&aq->lock);
	return rc;
}