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
struct netsec_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETSEC_RING_RX ; 
 int /*<<< orphan*/  NETSEC_RING_TX ; 
 struct netsec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netsec_free_dring (struct netsec_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netsec_netdev_uninit(struct net_device *ndev)
{
	struct netsec_priv *priv = netdev_priv(ndev);

	netsec_free_dring(priv, NETSEC_RING_RX);
	netsec_free_dring(priv, NETSEC_RING_TX);
}