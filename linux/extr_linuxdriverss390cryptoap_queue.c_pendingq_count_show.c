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
struct ap_queue {unsigned int pendingq_count; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_queue* to_ap_queue (struct device*) ; 

__attribute__((used)) static ssize_t pendingq_count_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct ap_queue *aq = to_ap_queue(dev);
	unsigned int penq_cnt = 0;

	spin_lock_bh(&aq->lock);
	penq_cnt = aq->pendingq_count;
	spin_unlock_bh(&aq->lock);
	return snprintf(buf, PAGE_SIZE, "%d\n", penq_cnt);
}