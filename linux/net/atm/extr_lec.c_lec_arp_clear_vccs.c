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
struct lec_vcc_priv {scalar_t__ xoff; int /*<<< orphan*/  old_pop; } ;
struct lec_arp_table {struct atm_vcc* recv_vcc; int /*<<< orphan*/  old_recv_push; struct atm_vcc* vcc; int /*<<< orphan*/  old_push; } ;
struct atm_vcc {int /*<<< orphan*/  push; int /*<<< orphan*/ * user_back; int /*<<< orphan*/  pop; scalar_t__ proto_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 struct lec_vcc_priv* LEC_VCC_PRIV (struct atm_vcc*) ; 
 int /*<<< orphan*/  kfree (struct lec_vcc_priv*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  vcc_release_async (struct atm_vcc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lec_arp_clear_vccs(struct lec_arp_table *entry)
{
	if (entry->vcc) {
		struct atm_vcc *vcc = entry->vcc;
		struct lec_vcc_priv *vpriv = LEC_VCC_PRIV(vcc);
		struct net_device *dev = (struct net_device *)vcc->proto_data;

		vcc->pop = vpriv->old_pop;
		if (vpriv->xoff)
			netif_wake_queue(dev);
		kfree(vpriv);
		vcc->user_back = NULL;
		vcc->push = entry->old_push;
		vcc_release_async(vcc, -EPIPE);
		entry->vcc = NULL;
	}
	if (entry->recv_vcc) {
		entry->recv_vcc->push = entry->old_recv_push;
		vcc_release_async(entry->recv_vcc, -EPIPE);
		entry->recv_vcc = NULL;
	}
}