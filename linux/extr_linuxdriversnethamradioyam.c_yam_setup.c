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
struct yam_port {int bitrate; int baudrate; int /*<<< orphan*/  send_queue; scalar_t__ irq; scalar_t__ iobase; struct net_device* dev; int /*<<< orphan*/  pers; int /*<<< orphan*/  slot; int /*<<< orphan*/  txtail; int /*<<< orphan*/  txd; int /*<<< orphan*/  holdd; scalar_t__ dupmode; int /*<<< orphan*/  magic; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; scalar_t__ irq; scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_AX25 ; 
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 int /*<<< orphan*/  AX25_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  AX25_MTU ; 
 int DEFAULT_BITRATE ; 
 int /*<<< orphan*/  DEFAULT_HOLDD ; 
 int /*<<< orphan*/  DEFAULT_PERS ; 
 int /*<<< orphan*/  DEFAULT_SLOT ; 
 int /*<<< orphan*/  DEFAULT_TXD ; 
 int /*<<< orphan*/  DEFAULT_TXTAIL ; 
 int /*<<< orphan*/  YAM_MAGIC ; 
 int /*<<< orphan*/  ax25_bcast ; 
 int /*<<< orphan*/  ax25_defaddr ; 
 int /*<<< orphan*/  ax25_header_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct yam_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yam_netdev_ops ; 

__attribute__((used)) static void yam_setup(struct net_device *dev)
{
	struct yam_port *yp = netdev_priv(dev);

	yp->magic = YAM_MAGIC;
	yp->bitrate = DEFAULT_BITRATE;
	yp->baudrate = DEFAULT_BITRATE * 2;
	yp->iobase = 0;
	yp->irq = 0;
	yp->dupmode = 0;
	yp->holdd = DEFAULT_HOLDD;
	yp->txd = DEFAULT_TXD;
	yp->txtail = DEFAULT_TXTAIL;
	yp->slot = DEFAULT_SLOT;
	yp->pers = DEFAULT_PERS;
	yp->dev = dev;

	dev->base_addr = yp->iobase;
	dev->irq = yp->irq;

	skb_queue_head_init(&yp->send_queue);

	dev->netdev_ops = &yam_netdev_ops;
	dev->header_ops = &ax25_header_ops;

	dev->type = ARPHRD_AX25;
	dev->hard_header_len = AX25_MAX_HEADER_LEN;
	dev->mtu = AX25_MTU;
	dev->addr_len = AX25_ADDR_LEN;
	memcpy(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	memcpy(dev->dev_addr, &ax25_defaddr, AX25_ADDR_LEN);
}