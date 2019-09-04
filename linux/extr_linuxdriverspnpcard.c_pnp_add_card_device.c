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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct pnp_dev {int /*<<< orphan*/  card_list; struct pnp_card* card; int /*<<< orphan*/  number; TYPE_1__* protocol; TYPE_2__ dev; int /*<<< orphan*/ * card_link; } ;
struct pnp_card {int /*<<< orphan*/  devices; int /*<<< orphan*/  number; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_lock ; 

int pnp_add_card_device(struct pnp_card *card, struct pnp_dev *dev)
{
	dev->dev.parent = &card->dev;
	dev->card_link = NULL;
	dev_set_name(&dev->dev, "%02x:%02x.%02x",
		     dev->protocol->number, card->number, dev->number);
	mutex_lock(&pnp_lock);
	dev->card = card;
	list_add_tail(&dev->card_list, &card->devices);
	mutex_unlock(&pnp_lock);
	return 0;
}