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
struct net_device {int tx_queue_len; scalar_t__ flags; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct hdlcdrv_channel_params {int member_0; int member_1; int member_2; int member_3; int /*<<< orphan*/  member_4; } ;
struct baycom_state {int /*<<< orphan*/ * skb; scalar_t__ ptt_keyed; struct hdlcdrv_channel_params ch_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_AX25 ; 
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 scalar_t__ AX25_BPQ_HEADER_LEN ; 
 int /*<<< orphan*/  AX25_DEF_PACLEN ; 
 scalar_t__ AX25_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  ax25_bcast ; 
 int /*<<< orphan*/  ax25_header_ops ; 
 int /*<<< orphan*/  baycom_netdev_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct baycom_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  null_ax25_address ; 

__attribute__((used)) static void baycom_probe(struct net_device *dev)
{
	const struct hdlcdrv_channel_params dflt_ch_params = { 
		20, 2, 10, 40, 0 
	};
	struct baycom_state *bc;

	/*
	 * not a real probe! only initialize data structures
	 */
	bc = netdev_priv(dev);
	/*
	 * initialize the baycom_state struct
	 */
	bc->ch_params = dflt_ch_params;
	bc->ptt_keyed = 0;

	/*
	 * initialize the device struct
	 */

	/* Fill in the fields of the device structure */
	bc->skb = NULL;
	
	dev->netdev_ops = &baycom_netdev_ops;
	dev->header_ops = &ax25_header_ops;
	
	dev->type = ARPHRD_AX25;           /* AF_AX25 device */
	dev->hard_header_len = AX25_MAX_HEADER_LEN + AX25_BPQ_HEADER_LEN;
	dev->mtu = AX25_DEF_PACLEN;        /* eth_mtu is the default */
	dev->addr_len = AX25_ADDR_LEN;     /* sizeof an ax.25 address */
	memcpy(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	memcpy(dev->dev_addr, &null_ax25_address, AX25_ADDR_LEN);
	dev->tx_queue_len = 16;

	/* New style flags */
	dev->flags = 0;
}