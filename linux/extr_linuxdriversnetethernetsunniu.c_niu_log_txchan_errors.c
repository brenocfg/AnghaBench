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
typedef  int u64 ;
struct tx_ring_info {int /*<<< orphan*/  tx_channel; } ;
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TX_CS_CONF_PART_ERR ; 
 int TX_CS_MBOX_ERR ; 
 int TX_CS_NACK_PKT_RD ; 
 int TX_CS_NACK_PREF ; 
 int TX_CS_PKT_PRT_ERR ; 
 int TX_CS_PKT_SIZE_ERR ; 
 int TX_CS_PREF_BUF_PAR_ERR ; 
 int TX_CS_TX_RING_OFLOW ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static void niu_log_txchan_errors(struct niu *np, struct tx_ring_info *rp,
				  u64 cs)
{
	netdev_err(np->dev, "TX channel %u errors ( ", rp->tx_channel);

	if (cs & TX_CS_MBOX_ERR)
		pr_cont("MBOX ");
	if (cs & TX_CS_PKT_SIZE_ERR)
		pr_cont("PKT_SIZE ");
	if (cs & TX_CS_TX_RING_OFLOW)
		pr_cont("TX_RING_OFLOW ");
	if (cs & TX_CS_PREF_BUF_PAR_ERR)
		pr_cont("PREF_BUF_PAR ");
	if (cs & TX_CS_NACK_PREF)
		pr_cont("NACK_PREF ");
	if (cs & TX_CS_NACK_PKT_RD)
		pr_cont("NACK_PKT_RD ");
	if (cs & TX_CS_CONF_PART_ERR)
		pr_cont("CONF_PART ");
	if (cs & TX_CS_PKT_PRT_ERR)
		pr_cont("PKT_PTR ");

	pr_cont(")\n");
}