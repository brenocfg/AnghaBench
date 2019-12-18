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
typedef  int u32 ;
struct sk_buff {scalar_t__ data; } ;
struct atm_vcc {int vpi; int vci; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* send ) (struct atm_vcc*,struct sk_buff*) ;} ;

/* Variables and functions */
 int ATM_HDR_VCI_MASK ; 
 int ATM_HDR_VCI_SHIFT ; 
 int ATM_HDR_VPI_MASK ; 
 int ATM_HDR_VPI_SHIFT ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int stub1 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static int atm_send_aal0(struct atm_vcc *vcc, struct sk_buff *skb)
{
	/*
	 * Note that if vpi/vci are _ANY or _UNSPEC the below will
	 * still work
	 */
	if (!capable(CAP_NET_ADMIN) &&
	    (((u32 *)skb->data)[0] & (ATM_HDR_VPI_MASK | ATM_HDR_VCI_MASK)) !=
	    ((vcc->vpi << ATM_HDR_VPI_SHIFT) |
	     (vcc->vci << ATM_HDR_VCI_SHIFT))) {
		kfree_skb(skb);
		return -EADDRNOTAVAIL;
	}
	return vcc->dev->ops->send(vcc, skb);
}