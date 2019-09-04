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
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; TYPE_2__* up; } ;
struct caif_device_entry {TYPE_1__ layer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ctrlcmd ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND ; 
 int /*<<< orphan*/  _CAIF_CTRLCMD_PHYIF_FLOW_ON_IND ; 
 struct caif_device_entry* caif_get (struct net_device*) ; 
 int /*<<< orphan*/  caifd_hold (struct caif_device_entry*) ; 
 int /*<<< orphan*/  caifd_put (struct caif_device_entry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_flowctrl(struct net_device *dev, int on)
{
	struct caif_device_entry *caifd;

	rcu_read_lock();

	caifd = caif_get(dev);
	if (!caifd || !caifd->layer.up || !caifd->layer.up->ctrlcmd) {
		rcu_read_unlock();
		return;
	}

	caifd_hold(caifd);
	rcu_read_unlock();

	caifd->layer.up->ctrlcmd(caifd->layer.up,
				 on ?
				 _CAIF_CTRLCMD_PHYIF_FLOW_ON_IND :
				 _CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND,
				 caifd->layer.id);
	caifd_put(caifd);
}