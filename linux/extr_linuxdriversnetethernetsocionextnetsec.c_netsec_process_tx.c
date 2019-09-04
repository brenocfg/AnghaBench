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
struct netsec_priv {struct net_device* ndev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int netsec_clean_tx_dring (struct netsec_priv*,int) ; 

__attribute__((used)) static int netsec_process_tx(struct netsec_priv *priv, int budget)
{
	struct net_device *ndev = priv->ndev;
	int new, done = 0;

	do {
		new = netsec_clean_tx_dring(priv, budget);
		done += new;
		budget -= new;
	} while (new);

	if (done && netif_queue_stopped(ndev))
		netif_wake_queue(ndev);

	return done;
}