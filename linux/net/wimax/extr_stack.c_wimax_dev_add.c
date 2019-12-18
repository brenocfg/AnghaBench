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
struct wimax_dev {int /*<<< orphan*/  mutex; struct net_device* net_dev; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  addr_str ;

/* Variables and functions */
 int /*<<< orphan*/  WIMAX_ST_DOWN ; 
 int /*<<< orphan*/  __wimax_state_set (struct wimax_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*,struct net_device*,...) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*,struct net_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wimax_addr_scnprint (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wimax_debugfs_add (struct wimax_dev*) ; 
 int /*<<< orphan*/  wimax_id_table_add (struct wimax_dev*) ; 
 int wimax_rfkill_add (struct wimax_dev*) ; 

int wimax_dev_add(struct wimax_dev *wimax_dev, struct net_device *net_dev)
{
	int result;
	struct device *dev = net_dev->dev.parent;
	char addr_str[32];

	d_fnstart(3, dev, "(wimax_dev %p net_dev %p)\n", wimax_dev, net_dev);

	/* Do the RFKILL setup before locking, as RFKILL will call
	 * into our functions.
	 */
	wimax_dev->net_dev = net_dev;
	result = wimax_rfkill_add(wimax_dev);
	if (result < 0)
		goto error_rfkill_add;

	/* Set up user-space interaction */
	mutex_lock(&wimax_dev->mutex);
	wimax_id_table_add(wimax_dev);
	wimax_debugfs_add(wimax_dev);

	__wimax_state_set(wimax_dev, WIMAX_ST_DOWN);
	mutex_unlock(&wimax_dev->mutex);

	wimax_addr_scnprint(addr_str, sizeof(addr_str),
			    net_dev->dev_addr, net_dev->addr_len);
	dev_err(dev, "WiMAX interface %s (%s) ready\n",
		net_dev->name, addr_str);
	d_fnend(3, dev, "(wimax_dev %p net_dev %p) = 0\n", wimax_dev, net_dev);
	return 0;

error_rfkill_add:
	d_fnend(3, dev, "(wimax_dev %p net_dev %p) = %d\n",
		wimax_dev, net_dev, result);
	return result;
}