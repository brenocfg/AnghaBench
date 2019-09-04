#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_2__* bus; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mac_addr; struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  event_list_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  wq; } ;
struct uwb_rc {int (* start ) (struct uwb_rc*) ;int ready; int /*<<< orphan*/  (* stop ) (struct uwb_rc*) ;TYPE_3__ uwb_dev; TYPE_1__ uwbd; void* priv; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  macbuf ;
typedef  int /*<<< orphan*/  devbuf ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int UWB_ADDR_STRSIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct uwb_rc*) ; 
 int /*<<< orphan*/  stub2 (struct uwb_rc*) ; 
 int uwb_dev_add (TYPE_3__*,struct device*,struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_dev_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_rm (TYPE_3__*) ; 
 int /*<<< orphan*/  uwb_mac_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rc_new_index () ; 
 int uwb_rc_setup (struct uwb_rc*) ; 
 int uwb_rc_sys_add (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwbd_start (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwbd_stop (struct uwb_rc*) ; 

int uwb_rc_add(struct uwb_rc *rc, struct device *parent_dev, void *priv)
{
	int result;
	struct device *dev;
	char macbuf[UWB_ADDR_STRSIZE], devbuf[UWB_ADDR_STRSIZE];

	rc->index = uwb_rc_new_index();

	dev = &rc->uwb_dev.dev;
	dev_set_name(dev, "uwb%d", rc->index);

	rc->priv = priv;

	init_waitqueue_head(&rc->uwbd.wq);
	INIT_LIST_HEAD(&rc->uwbd.event_list);
	spin_lock_init(&rc->uwbd.event_list_lock);

	uwbd_start(rc);

	result = rc->start(rc);
	if (result < 0)
		goto error_rc_start;

	result = uwb_rc_setup(rc);
	if (result < 0) {
		dev_err(dev, "cannot setup UWB radio controller: %d\n", result);
		goto error_rc_setup;
	}

	result = uwb_dev_add(&rc->uwb_dev, parent_dev, rc);
	if (result < 0 && result != -EADDRNOTAVAIL)
		goto error_dev_add;

	result = uwb_rc_sys_add(rc);
	if (result < 0) {
		dev_err(parent_dev, "cannot register UWB radio controller "
			"dev attributes: %d\n", result);
		goto error_sys_add;
	}

	uwb_mac_addr_print(macbuf, sizeof(macbuf), &rc->uwb_dev.mac_addr);
	uwb_dev_addr_print(devbuf, sizeof(devbuf), &rc->uwb_dev.dev_addr);
	dev_info(dev,
		 "new uwb radio controller (mac %s dev %s) on %s %s\n",
		 macbuf, devbuf, parent_dev->bus->name, dev_name(parent_dev));
	rc->ready = 1;
	return 0;

error_sys_add:
	uwb_dev_rm(&rc->uwb_dev);
error_dev_add:
error_rc_setup:
	rc->stop(rc);
error_rc_start:
	uwbd_stop(rc);
	return result;
}