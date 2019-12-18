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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  flow_indr_block_bind_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  __flow_indr_block_cb_unregister (struct net_device*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void flow_indr_block_cb_unregister(struct net_device *dev,
				   flow_indr_block_bind_cb_t *cb,
				   void *cb_ident)
{
	rtnl_lock();
	__flow_indr_block_cb_unregister(dev, cb, cb_ident);
	rtnl_unlock();
}