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
struct atm_vcc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/ * atmarpd ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 TYPE_1__* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atmarpd_close(struct atm_vcc *vcc)
{
	pr_debug("\n");

	rtnl_lock();
	atmarpd = NULL;
	skb_queue_purge(&sk_atm(vcc)->sk_receive_queue);
	rtnl_unlock();

	pr_debug("(done)\n");
	module_put(THIS_MODULE);
}