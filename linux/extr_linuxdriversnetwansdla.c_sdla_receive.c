#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct sdla_cmd {int opp_flag; short dlci; short length; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int mem_start; TYPE_1__ stats; } ;
struct frhdr {int dummy; } ;
struct frad_local {int type; int buffer; short* dlci; struct net_device** master; } ;
struct dlci_local {int /*<<< orphan*/  (* receive ) (struct sk_buff*,struct net_device*) ;} ;
struct buf_info {int buf_top; int buf_base; int rse_num; int /*<<< orphan*/  rse_base; } ;
struct buf_entry {int opp_flag; short dlci; short length; int buf_addr; } ;

/* Variables and functions */
 int CONFIG_DLCI_MAX ; 
 int SDLA_502_DATA_OFS ; 
 int SDLA_502_RCV_BUF ; 
 int SDLA_508_RXBUF_INFO ; 
 int SDLA_ADDR_MASK ; 
#define  SDLA_S502A 130 
#define  SDLA_S502E 129 
#define  SDLA_S508 128 
 int /*<<< orphan*/  SDLA_WINDOW (struct net_device*,int) ; 
 int /*<<< orphan*/  __sdla_read (struct net_device*,int,int /*<<< orphan*/ ,short) ; 
 struct sk_buff* dev_alloc_skb (short) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,...) ; 
 void* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sdla_lock ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static void sdla_receive(struct net_device *dev)
{
	struct net_device	  *master;
	struct frad_local *flp;
	struct dlci_local *dlp;
	struct sk_buff	 *skb;

	struct sdla_cmd	*cmd;
	struct buf_info	*pbufi;
	struct buf_entry  *pbuf;

	unsigned long	  flags;
	int               i=0, received, success, addr, buf_base, buf_top;
	short             dlci, len, len2, split;

	flp = netdev_priv(dev);
	success = 1;
	received = addr = buf_top = buf_base = 0;
	len = dlci = 0;
	skb = NULL;
	master = NULL;
	cmd = NULL;
	pbufi = NULL;
	pbuf = NULL;

	spin_lock_irqsave(&sdla_lock, flags);

	switch (flp->type)
	{
		case SDLA_S502A:
		case SDLA_S502E:
			cmd = (void *) (dev->mem_start + (SDLA_502_RCV_BUF & SDLA_ADDR_MASK));
			SDLA_WINDOW(dev, SDLA_502_RCV_BUF);
			success = cmd->opp_flag;
			if (!success)
				break;

			dlci = cmd->dlci;
			len = cmd->length;
			break;

		case SDLA_S508:
			pbufi = (void *) (dev->mem_start + (SDLA_508_RXBUF_INFO & SDLA_ADDR_MASK));
			SDLA_WINDOW(dev, SDLA_508_RXBUF_INFO);
			pbuf = (void *) (dev->mem_start + ((pbufi->rse_base + flp->buffer * sizeof(struct buf_entry)) & SDLA_ADDR_MASK));
			success = pbuf->opp_flag;
			if (!success)
				break;

			buf_top = pbufi->buf_top;
			buf_base = pbufi->buf_base;
			dlci = pbuf->dlci;
			len = pbuf->length;
			addr = pbuf->buf_addr;
			break;
	}

	/* common code, find the DLCI and get the SKB */
	if (success)
	{
		for (i=0;i<CONFIG_DLCI_MAX;i++)
			if (flp->dlci[i] == dlci)
				break;

		if (i == CONFIG_DLCI_MAX)
		{
			netdev_notice(dev, "Received packet from invalid DLCI %i, ignoring\n",
				      dlci);
			dev->stats.rx_errors++;
			success = 0;
		}
	}

	if (success)
	{
		master = flp->master[i];
		skb = dev_alloc_skb(len + sizeof(struct frhdr));
		if (skb == NULL) 
		{
			netdev_notice(dev, "Memory squeeze, dropping packet\n");
			dev->stats.rx_dropped++;
			success = 0;
		}
		else
			skb_reserve(skb, sizeof(struct frhdr));
	}

	/* pick up the data */
	switch (flp->type)
	{
		case SDLA_S502A:
		case SDLA_S502E:
			if (success)
				__sdla_read(dev, SDLA_502_RCV_BUF + SDLA_502_DATA_OFS, skb_put(skb,len), len);

			SDLA_WINDOW(dev, SDLA_502_RCV_BUF);
			cmd->opp_flag = 0;
			break;

		case SDLA_S508:
			if (success)
			{
				/* is this buffer split off the end of the internal ring buffer */
				split = addr + len > buf_top + 1 ? len - (buf_top - addr + 1) : 0;
				len2 = len - split;

				__sdla_read(dev, addr, skb_put(skb, len2), len2);
				if (split)
					__sdla_read(dev, buf_base, skb_put(skb, split), split);
			}

			/* increment the buffer we're looking at */
			SDLA_WINDOW(dev, SDLA_508_RXBUF_INFO);
			flp->buffer = (flp->buffer + 1) % pbufi->rse_num;
			pbuf->opp_flag = 0;
			break;
	}

	if (success)
	{
		dev->stats.rx_packets++;
		dlp = netdev_priv(master);
		(*dlp->receive)(skb, master);
	}

	spin_unlock_irqrestore(&sdla_lock, flags);
}