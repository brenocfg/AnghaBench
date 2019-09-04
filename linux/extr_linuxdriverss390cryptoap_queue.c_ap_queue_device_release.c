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
struct device {int dummy; } ;
struct ap_queue {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_list_lock ; 
 int /*<<< orphan*/  kfree (struct ap_queue*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_queue* to_ap_queue (struct device*) ; 

__attribute__((used)) static void ap_queue_device_release(struct device *dev)
{
	struct ap_queue *aq = to_ap_queue(dev);

	if (!list_empty(&aq->list)) {
		spin_lock_bh(&ap_list_lock);
		list_del_init(&aq->list);
		spin_unlock_bh(&ap_list_lock);
	}
	kfree(aq);
}