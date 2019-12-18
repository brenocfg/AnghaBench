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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct lec_vcc_priv {scalar_t__ xoff; int /*<<< orphan*/  (* old_pop ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 struct lec_vcc_priv* LEC_VCC_PRIV (struct atm_vcc*) ; 
 scalar_t__ atm_may_send (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static void lec_pop(struct atm_vcc *vcc, struct sk_buff *skb)
{
	struct lec_vcc_priv *vpriv = LEC_VCC_PRIV(vcc);
	struct net_device *dev = skb->dev;

	if (vpriv == NULL) {
		pr_info("vpriv = NULL!?!?!?\n");
		return;
	}

	vpriv->old_pop(vcc, skb);

	if (vpriv->xoff && atm_may_send(vcc, 0)) {
		vpriv->xoff = 0;
		if (netif_running(dev) && netif_queue_stopped(dev))
			netif_wake_queue(dev);
	}
}