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
struct net_device {int /*<<< orphan*/  dn_ptr; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_3__ {int t2; int t3; } ;
struct dn_dev {TYPE_2__ timer; TYPE_1__ parms; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 struct dn_dev* rcu_dereference_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dn_dev_set_timer(struct net_device *dev)
{
	struct dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);

	if (dn_db->parms.t2 > dn_db->parms.t3)
		dn_db->parms.t2 = dn_db->parms.t3;

	dn_db->timer.expires = jiffies + (dn_db->parms.t2 * HZ);

	add_timer(&dn_db->timer);
}