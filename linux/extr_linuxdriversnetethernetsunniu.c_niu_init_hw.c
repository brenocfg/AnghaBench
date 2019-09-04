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
struct tx_ring_info {int dummy; } ;
struct niu {int num_tx_rings; int /*<<< orphan*/  dev; struct tx_ring_info* tx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_printk (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  niu_disable_ipp (struct niu*) ; 
 int niu_init_classifier_hw (struct niu*) ; 
 int niu_init_ipp (struct niu*) ; 
 int niu_init_mac (struct niu*) ; 
 int niu_init_one_tx_channel (struct niu*,struct tx_ring_info*) ; 
 int niu_init_rx_channels (struct niu*) ; 
 int niu_init_zcp (struct niu*) ; 
 int /*<<< orphan*/  niu_reset_rx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_reset_tx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_rx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_tx_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_txc_enable_port (struct niu*,int) ; 
 int /*<<< orphan*/  niu_txc_port_dma_enable (struct niu*,int) ; 
 int /*<<< orphan*/  niu_txc_set_imask (struct niu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_init_hw(struct niu *np)
{
	int i, err;

	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Initialize TXC\n");
	niu_txc_enable_port(np, 1);
	niu_txc_port_dma_enable(np, 1);
	niu_txc_set_imask(np, 0);

	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Initialize TX channels\n");
	for (i = 0; i < np->num_tx_rings; i++) {
		struct tx_ring_info *rp = &np->tx_rings[i];

		err = niu_init_one_tx_channel(np, rp);
		if (err)
			return err;
	}

	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Initialize RX channels\n");
	err = niu_init_rx_channels(np);
	if (err)
		goto out_uninit_tx_channels;

	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Initialize classifier\n");
	err = niu_init_classifier_hw(np);
	if (err)
		goto out_uninit_rx_channels;

	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Initialize ZCP\n");
	err = niu_init_zcp(np);
	if (err)
		goto out_uninit_rx_channels;

	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Initialize IPP\n");
	err = niu_init_ipp(np);
	if (err)
		goto out_uninit_rx_channels;

	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Initialize MAC\n");
	err = niu_init_mac(np);
	if (err)
		goto out_uninit_ipp;

	return 0;

out_uninit_ipp:
	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Uninit IPP\n");
	niu_disable_ipp(np);

out_uninit_rx_channels:
	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Uninit RX channels\n");
	niu_stop_rx_channels(np);
	niu_reset_rx_channels(np);

out_uninit_tx_channels:
	netif_printk(np, ifup, KERN_DEBUG, np->dev, "Uninit TX channels\n");
	niu_stop_tx_channels(np);
	niu_reset_tx_channels(np);

	return err;
}