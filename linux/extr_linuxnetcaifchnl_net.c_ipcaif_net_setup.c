#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int needs_free_netdev; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  connection_id; } ;
struct TYPE_8__ {TYPE_2__ dgm; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
struct TYPE_10__ {TYPE_4__ sockaddr; int /*<<< orphan*/  priority; int /*<<< orphan*/  link_selector; int /*<<< orphan*/  protocol; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrlcmd; int /*<<< orphan*/  receive; } ;
struct chnl_net {int flowenabled; int /*<<< orphan*/  netmgmt_wq; TYPE_5__ conn_req; struct net_device* netdev; TYPE_1__ chnl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIFPROTO_DATAGRAM ; 
 int /*<<< orphan*/  CAIF_LINK_HIGH_BANDW ; 
 int /*<<< orphan*/  CAIF_NET_DEFAULT_QUEUE_LEN ; 
 int /*<<< orphan*/  CAIF_PRIO_LOW ; 
 int /*<<< orphan*/  GPRS_PDP_MTU ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_POINTOPOINT ; 
 int /*<<< orphan*/  UNDEF_CONNID ; 
 int /*<<< orphan*/  chnl_flowctrl_cb ; 
 int /*<<< orphan*/  chnl_net_destructor ; 
 int /*<<< orphan*/  chnl_recv_cb ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_ops ; 
 struct chnl_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ipcaif_net_setup(struct net_device *dev)
{
	struct chnl_net *priv;
	dev->netdev_ops = &netdev_ops;
	dev->needs_free_netdev = true;
	dev->priv_destructor = chnl_net_destructor;
	dev->flags |= IFF_NOARP;
	dev->flags |= IFF_POINTOPOINT;
	dev->mtu = GPRS_PDP_MTU;
	dev->tx_queue_len = CAIF_NET_DEFAULT_QUEUE_LEN;

	priv = netdev_priv(dev);
	priv->chnl.receive = chnl_recv_cb;
	priv->chnl.ctrlcmd = chnl_flowctrl_cb;
	priv->netdev = dev;
	priv->conn_req.protocol = CAIFPROTO_DATAGRAM;
	priv->conn_req.link_selector = CAIF_LINK_HIGH_BANDW;
	priv->conn_req.priority = CAIF_PRIO_LOW;
	/* Insert illegal value */
	priv->conn_req.sockaddr.u.dgm.connection_id = UNDEF_CONNID;
	priv->flowenabled = false;

	init_waitqueue_head(&priv->netmgmt_wq);
}