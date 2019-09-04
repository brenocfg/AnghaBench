#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_6__ {struct list_head* next; } ;
struct pnp_dev {struct pnp_card_link* card_link; TYPE_3__ dev; int /*<<< orphan*/  id; TYPE_1__ card_list; struct pnp_card* card; } ;
struct pnp_card_link {struct pnp_card_driver* driver; struct pnp_card* card; } ;
struct TYPE_7__ {int /*<<< orphan*/  driver; } ;
struct pnp_card_driver {TYPE_2__ link; } ;
struct list_head {struct list_head* next; } ;
struct pnp_card {struct list_head devices; } ;
struct TYPE_9__ {scalar_t__ (* probe ) (TYPE_3__*) ;} ;

/* Variables and functions */
 struct pnp_dev* card_to_pnp_dev (struct list_head*) ; 
 scalar_t__ compare_pnp_id (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ device_bind_driver (TYPE_3__*) ; 
 TYPE_4__ pnp_bus_type ; 
 scalar_t__ stub1 (TYPE_3__*) ; 

struct pnp_dev *pnp_request_card_device(struct pnp_card_link *clink,
					const char *id, struct pnp_dev *from)
{
	struct list_head *pos;
	struct pnp_dev *dev;
	struct pnp_card_driver *drv;
	struct pnp_card *card;

	if (!clink || !id)
		return NULL;

	card = clink->card;
	drv = clink->driver;
	if (!from) {
		pos = card->devices.next;
	} else {
		if (from->card != card)
			return NULL;
		pos = from->card_list.next;
	}
	while (pos != &card->devices) {
		dev = card_to_pnp_dev(pos);
		if ((!dev->card_link) && compare_pnp_id(dev->id, id))
			goto found;
		pos = pos->next;
	}

	return NULL;

found:
	dev->card_link = clink;
	dev->dev.driver = &drv->link.driver;
	if (pnp_bus_type.probe(&dev->dev))
		goto err_out;
	if (device_bind_driver(&dev->dev))
		goto err_out;

	return dev;

err_out:
	dev->dev.driver = NULL;
	dev->card_link = NULL;
	return NULL;
}