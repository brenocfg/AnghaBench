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
struct fw_iso_resources {int allocated; int bandwidth; int bandwidth_overhead; int channel; int /*<<< orphan*/  mutex; TYPE_2__* unit; int /*<<< orphan*/  channels_mask; int /*<<< orphan*/  generation; } ;
struct fw_card {int /*<<< orphan*/  lock; int /*<<< orphan*/  generation; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {struct fw_card* card; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADFD ; 
 int EBUSY ; 
 scalar_t__ WARN_ON (int) ; 
 int current_bandwidth_overhead (struct fw_card*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fw_iso_resource_manage (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 TYPE_1__* fw_parent_device (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int packet_bandwidth (unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int wait_isoch_resource_delay_after_bus_reset (struct fw_card*) ; 

int fw_iso_resources_allocate(struct fw_iso_resources *r,
			      unsigned int max_payload_bytes, int speed)
{
	struct fw_card *card = fw_parent_device(r->unit)->card;
	int bandwidth, channel, err;

	if (WARN_ON(r->allocated))
		return -EBADFD;

	r->bandwidth = packet_bandwidth(max_payload_bytes, speed);

retry_after_bus_reset:
	spin_lock_irq(&card->lock);
	r->generation = card->generation;
	r->bandwidth_overhead = current_bandwidth_overhead(card);
	spin_unlock_irq(&card->lock);

	err = wait_isoch_resource_delay_after_bus_reset(card);
	if (err < 0)
		return err;

	mutex_lock(&r->mutex);

	bandwidth = r->bandwidth + r->bandwidth_overhead;
	fw_iso_resource_manage(card, r->generation, r->channels_mask,
			       &channel, &bandwidth, true);
	if (channel == -EAGAIN) {
		mutex_unlock(&r->mutex);
		goto retry_after_bus_reset;
	}
	if (channel >= 0) {
		r->channel = channel;
		r->allocated = true;
	} else {
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