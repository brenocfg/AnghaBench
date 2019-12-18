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
struct sk_buff {int dummy; } ;
struct nfc_llc {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rcv_from_drv ) (struct nfc_llc*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfc_llc*,struct sk_buff*) ; 

void nfc_llc_rcv_from_drv(struct nfc_llc *llc, struct sk_buff *skb)
{
	llc->ops->rcv_from_drv(llc, skb);
}