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
struct ioc3_private {int rx_ci; int rx_pi; int tx_pi; int tx_ci; scalar_t__ txqlen; int /*<<< orphan*/  txr; int /*<<< orphan*/  rxr; struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int ERPIR_ARM ; 
 int /*<<< orphan*/  ioc3_alloc_rings (struct net_device*) ; 
 int /*<<< orphan*/  ioc3_clean_rx_ring (struct ioc3_private*) ; 
 int /*<<< orphan*/  ioc3_clean_tx_ring (struct ioc3_private*) ; 
 int /*<<< orphan*/  ioc3_free_rings (struct ioc3_private*) ; 
 unsigned long ioc3_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_r_etcir () ; 
 int /*<<< orphan*/  ioc3_w_erbr_h (unsigned long) ; 
 int /*<<< orphan*/  ioc3_w_erbr_l (unsigned long) ; 
 int /*<<< orphan*/  ioc3_w_ercir (int) ; 
 int /*<<< orphan*/  ioc3_w_erpir (int) ; 
 int /*<<< orphan*/  ioc3_w_etbr_h (unsigned long) ; 
 int /*<<< orphan*/  ioc3_w_etbr_l (unsigned long) ; 
 int /*<<< orphan*/  ioc3_w_etcir (int) ; 
 int /*<<< orphan*/  ioc3_w_etpir (int) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ioc3_init_rings(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;
	unsigned long ring;

	ioc3_free_rings(ip);
	ioc3_alloc_rings(dev);

	ioc3_clean_rx_ring(ip);
	ioc3_clean_tx_ring(ip);

	/* Now the rx ring base, consume & produce registers.  */
	ring = ioc3_map(ip->rxr, 0);
	ioc3_w_erbr_h(ring >> 32);
	ioc3_w_erbr_l(ring & 0xffffffff);
	ioc3_w_ercir(ip->rx_ci << 3);
	ioc3_w_erpir((ip->rx_pi << 3) | ERPIR_ARM);

	ring = ioc3_map(ip->txr, 0);

	ip->txqlen = 0;					/* nothing queued  */

	/* Now the tx ring base, consume & produce registers.  */
	ioc3_w_etbr_h(ring >> 32);
	ioc3_w_etbr_l(ring & 0xffffffff);
	ioc3_w_etpir(ip->tx_pi << 7);
	ioc3_w_etcir(ip->tx_ci << 7);
	(void) ioc3_r_etcir();				/* Flush */
}