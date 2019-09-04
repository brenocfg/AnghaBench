#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fw_iso_resources {int allocated; int bandwidth_overhead; int bandwidth; unsigned long long channel; int /*<<< orphan*/  mutex; TYPE_2__* unit; int /*<<< orphan*/  generation; } ;
struct fw_card {int /*<<< orphan*/  lock; int /*<<< orphan*/  generation; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {struct fw_card* card; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int current_bandwidth_overhead (struct fw_card*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fw_iso_resource_manage (struct fw_card*,int /*<<< orphan*/ ,unsigned long long,int*,int*,int) ; 
 TYPE_1__* fw_parent_device (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int fw_iso_resources_update(struct fw_iso_resources *r)
{
	struct fw_card *card = fw_parent_device(r->unit)->card;
	int bandwidth, channel;

	mutex_lock(&r->mutex);

	if (!r->allocated) {
		mutex_unlock(&r->mutex);
		return 0;
	}

	spin_lock_irq(&card->lock);
	r->generation = card->generation;
	r->bandwidth_overhead = current_bandwidth_overhead(card);
	spin_unlock_irq(&card->lock);

	bandwidth = r->bandwidth + r->bandwidth_overhead;

	fw_iso_resource_manage(card, r->generation, 1uLL << r->channel,
			       &channel, &bandwidth, true);
	/*
	 * When another bus reset happens, pretend that the allocation
	 * succeeded; we will try again for the new generation later.
	 */
	if (channel < 0 && channel != -EAGAIN) {
		r->allocated = false;
		if (channel == -EBUSY)
			dev_err(&r->unit->device,
				"isochronous resources exhausted\n");
		else
			dev_err(&r->unit->device,
				"isochronous resource allocation failed\n");
	}

	mutex_unlock(&r->mutex);

	return channel;
}