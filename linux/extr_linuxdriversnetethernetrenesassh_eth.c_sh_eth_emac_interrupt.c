#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sh_eth_private {scalar_t__ ether_link_active_low; scalar_t__ no_ether_link; TYPE_3__* cd; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_carrier_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_6__ {scalar_t__ no_psr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECSIPR ; 
 int /*<<< orphan*/  ECSR ; 
 int ECSR_ICD ; 
 int ECSR_LCHNG ; 
 int ECSR_MPD ; 
 int /*<<< orphan*/  EESIPR ; 
 int /*<<< orphan*/  EESIPR_ECIIP ; 
 int PHY_ST_LINK ; 
 int /*<<< orphan*/  PSR ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_rcv_snd_disable (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_rcv_snd_enable (struct net_device*) ; 
 int sh_eth_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_eth_emac_interrupt(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u32 felic_stat;
	u32 link_stat;

	felic_stat = sh_eth_read(ndev, ECSR) & sh_eth_read(ndev, ECSIPR);
	sh_eth_write(ndev, felic_stat, ECSR);	/* clear int */
	if (felic_stat & ECSR_ICD)
		ndev->stats.tx_carrier_errors++;
	if (felic_stat & ECSR_MPD)
		pm_wakeup_event(&mdp->pdev->dev, 0);
	if (felic_stat & ECSR_LCHNG) {
		/* Link Changed */
		if (mdp->cd->no_psr || mdp->no_ether_link)
			return;
		link_stat = sh_eth_read(ndev, PSR);
		if (mdp->ether_link_active_low)
			link_stat = ~link_stat;
		if (!(link_stat & PHY_ST_LINK)) {
			sh_eth_rcv_snd_disable(ndev);
		} else {
			/* Link Up */
			sh_eth_modify(ndev, EESIPR, EESIPR_ECIIP, 0);
			/* clear int */
			sh_eth_modify(ndev, ECSR, 0, 0);
			sh_eth_modify(ndev, EESIPR, EESIPR_ECIIP, EESIPR_ECIIP);
			/* enable tx and rx */
			sh_eth_rcv_snd_enable(ndev);
		}
	}
}