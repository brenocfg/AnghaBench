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
struct net_device {int /*<<< orphan*/  state; int /*<<< orphan*/  napi_list; int /*<<< orphan*/  reg_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NETREG_DUMMY ; 
 int /*<<< orphan*/  __LINK_STATE_PRESENT ; 
 int /*<<< orphan*/  __LINK_STATE_START ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memset (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int init_dummy_netdev(struct net_device *dev)
{
	/* Clear everything. Note we don't initialize spinlocks
	 * are they aren't supposed to be taken by any of the
	 * NAPI code and this dummy netdev is supposed to be
	 * only ever used for NAPI polls
	 */
	memset(dev, 0, sizeof(struct net_device));

	/* make sure we BUG if trying to hit standard
	 * register/unregister code path
	 */
	dev->reg_state = NETREG_DUMMY;

	/* NAPI wants this */
	INIT_LIST_HEAD(&dev->napi_list);

	/* a dummy interface is started by default */
	set_bit(__LINK_STATE_PRESENT, &dev->state);
	set_bit(__LINK_STATE_START, &dev->state);

	/* napi_busy_loop stats accounting wants this */
	dev_net_set(dev, &init_net);

	/* Note : We dont allocate pcpu_refcnt for dummy devices,
	 * because users of this 'device' dont need to change
	 * its refcount.
	 */

	return 0;
}