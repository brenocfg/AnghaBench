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
 int netsec_alloc_dring (struct netsec_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netsec_free_dring (struct netsec_priv*,int /*<<< orphan*/ ) ; 
 int netsec_reset_hardware (struct netsec_priv*,int) ; 

__attribute__((used)) static int netsec_netdev_init(struct net_device *ndev)
{
	struct netsec_priv *priv = netdev_priv(ndev);
	int ret;

	ret = netsec_alloc_dring(priv, NETSEC_RING_TX);
	if (ret)
		return ret;

	ret = netsec_alloc_dring(priv, NETSEC_RING_RX);
	if (ret)
		goto err1;

	ret = netsec_reset_hardware(priv, true);
	if (ret)
		goto err2;

	return 0;
err2:
	netsec_free_dring(priv, NETSEC_RING_RX);
err1:
	netsec_free_dring(priv, NETSEC_RING_TX);
	return ret;
}