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
struct sk_buff {int dummy; } ;
struct br2684_vcc {int /*<<< orphan*/  device; int /*<<< orphan*/  qspace; int /*<<< orphan*/  (* old_pop ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 struct br2684_vcc* BR2684_VCC (struct atm_vcc*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static void br2684_pop(struct atm_vcc *vcc, struct sk_buff *skb)
{
	struct br2684_vcc *brvcc = BR2684_VCC(vcc);

	pr_debug("(vcc %p ; net_dev %p )\n", vcc, brvcc->device);
	brvcc->old_pop(vcc, skb);

	/* If the queue space just went up from zero, wake */
	if (atomic_inc_return(&brvcc->qspace) == 1)
		netif_wake_queue(brvcc->device);
}