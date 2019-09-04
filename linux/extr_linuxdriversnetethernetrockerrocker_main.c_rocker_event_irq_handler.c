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
typedef  scalar_t__ u32 ;
struct rocker_desc_info {int dummy; } ;
struct rocker {int /*<<< orphan*/  event_ring; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int rocker_desc_err (struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_desc_gen_clear (struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_desc_head_set (struct rocker*,int /*<<< orphan*/ *,struct rocker_desc_info const*) ; 
 struct rocker_desc_info* rocker_desc_tail_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_dma_ring_credits_set (struct rocker*,int /*<<< orphan*/ *,scalar_t__) ; 
 int rocker_event_process (struct rocker*,struct rocker_desc_info const*) ; 

__attribute__((used)) static irqreturn_t rocker_event_irq_handler(int irq, void *dev_id)
{
	struct rocker *rocker = dev_id;
	const struct pci_dev *pdev = rocker->pdev;
	const struct rocker_desc_info *desc_info;
	u32 credits = 0;
	int err;

	while ((desc_info = rocker_desc_tail_get(&rocker->event_ring))) {
		err = rocker_desc_err(desc_info);
		if (err) {
			dev_err(&pdev->dev, "event desc received with err %d\n",
				err);
		} else {
			err = rocker_event_process(rocker, desc_info);
			if (err)
				dev_err(&pdev->dev, "event processing failed with err %d\n",
					err);
		}
		rocker_desc_gen_clear(desc_info);
		rocker_desc_head_set(rocker, &rocker->event_ring, desc_info);
		credits++;
	}
	rocker_dma_ring_credits_set(rocker, &rocker->event_ring, credits);

	return IRQ_HANDLED;
}