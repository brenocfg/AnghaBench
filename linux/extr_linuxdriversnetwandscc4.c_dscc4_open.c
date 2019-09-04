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
struct dscc4_dev_priv {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR0 ; 
 int /*<<< orphan*/  CCR2 ; 
 int /*<<< orphan*/  CMDR ; 
 int EAGAIN ; 
 int EventsMask ; 
 int FakeReset ; 
 int /*<<< orphan*/  IMR ; 
 int NeedIDR ; 
 int NeedIDT ; 
 int PowerUp ; 
 int RxSccRes ; 
 int SccBusy ; 
 int TxSccRes ; 
 int Vis ; 
 int debug ; 
 scalar_t__ dscc4_loopback_check (struct dscc4_dev_priv*) ; 
 struct dscc4_dev_priv* dscc4_priv (struct net_device*) ; 
 int /*<<< orphan*/  dscc4_tx_print (struct net_device*,struct dscc4_dev_priv*,char*) ; 
 int dscc4_wait_ack_cec (struct dscc4_dev_priv*,struct net_device*,char*) ; 
 int dscc4_xpr_ack (struct dscc4_dev_priv*) ; 
 int /*<<< orphan*/  hdlc_close (struct net_device*) ; 
 int hdlc_open (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  scc_patchl (int,int,struct dscc4_dev_priv*,struct net_device*,int /*<<< orphan*/ ) ; 
 int scc_readl_star (struct dscc4_dev_priv*,struct net_device*) ; 
 int /*<<< orphan*/  scc_writel (int,struct dscc4_dev_priv*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dscc4_open(struct net_device *dev)
{
	struct dscc4_dev_priv *dpriv = dscc4_priv(dev);
	int ret = -EAGAIN;

	if ((dscc4_loopback_check(dpriv) < 0))
		goto err;

	if ((ret = hdlc_open(dev)))
		goto err;

	/*
	 * Due to various bugs, there is no way to reliably reset a
	 * specific port (manufacturer's dependent special PCI #RST wiring
	 * apart: it affects all ports). Thus the device goes in the best
	 * silent mode possible at dscc4_close() time and simply claims to
	 * be up if it's opened again. It still isn't possible to change
	 * the HDLC configuration without rebooting but at least the ports
	 * can be up/down ifconfig'ed without killing the host.
	 */
	if (dpriv->flags & FakeReset) {
		dpriv->flags &= ~FakeReset;
		scc_patchl(0, PowerUp, dpriv, dev, CCR0);
		scc_patchl(0, 0x00050000, dpriv, dev, CCR2);
		scc_writel(EventsMask, dpriv, dev, IMR);
		netdev_info(dev, "up again\n");
		goto done;
	}

	/* IDT+IDR during XPR */
	dpriv->flags = NeedIDR | NeedIDT;

	scc_patchl(0, PowerUp | Vis, dpriv, dev, CCR0);

	/*
	 * The following is a bit paranoid...
	 *
	 * NB: the datasheet "...CEC will stay active if the SCC is in
	 * power-down mode or..." and CCR2.RAC = 1 are two different
	 * situations.
	 */
	if (scc_readl_star(dpriv, dev) & SccBusy) {
		netdev_err(dev, "busy - try later\n");
		ret = -EAGAIN;
		goto err_out;
	} else
		netdev_info(dev, "available - good\n");

	scc_writel(EventsMask, dpriv, dev, IMR);

	/* Posted write is flushed in the wait_ack loop */
	scc_writel(TxSccRes | RxSccRes, dpriv, dev, CMDR);

	if ((ret = dscc4_wait_ack_cec(dpriv, dev, "Cec")) < 0)
		goto err_disable_scc_events;

	/*
	 * I would expect XPR near CE completion (before ? after ?).
	 * At worst, this code won't see a late XPR and people
	 * will have to re-issue an ifconfig (this is harmless).
	 * WARNING, a really missing XPR usually means a hardware
	 * reset is needed. Suggestions anyone ?
	 */
	if ((ret = dscc4_xpr_ack(dpriv)) < 0) {
		pr_err("XPR timeout\n");
		goto err_disable_scc_events;
	}
	
	if (debug > 2)
		dscc4_tx_print(dev, dpriv, "Open");

done:
	netif_start_queue(dev);

	netif_carrier_on(dev);

	return 0;

err_disable_scc_events:
	scc_writel(0xffffffff, dpriv, dev, IMR);
	scc_patchl(PowerUp | Vis, 0, dpriv, dev, CCR0);
err_out:
	hdlc_close(dev);
err:
	return ret;
}