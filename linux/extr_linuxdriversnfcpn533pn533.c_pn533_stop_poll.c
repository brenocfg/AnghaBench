#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pn533 {int /*<<< orphan*/  poll_work; TYPE_1__* phy_ops; int /*<<< orphan*/  dev; int /*<<< orphan*/  poll_mod_count; int /*<<< orphan*/  listen_timer; } ;
struct nfc_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* abort_cmd ) (struct pn533*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 struct pn533* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pn533_poll_reset_mod_list (struct pn533*) ; 
 int /*<<< orphan*/  stub1 (struct pn533*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pn533_stop_poll(struct nfc_dev *nfc_dev)
{
	struct pn533 *dev = nfc_get_drvdata(nfc_dev);

	del_timer(&dev->listen_timer);

	if (!dev->poll_mod_count) {
		dev_dbg(dev->dev,
			"Polling operation was not running\n");
		return;
	}

	dev->phy_ops->abort_cmd(dev, GFP_KERNEL);
	flush_delayed_work(&dev->poll_work);
	pn533_poll_reset_mod_list(dev);
}