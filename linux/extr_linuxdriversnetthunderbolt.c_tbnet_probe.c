#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thunderbolt_ip_frame_header {int dummy; } ;
struct TYPE_3__ {struct tbnet* data; int /*<<< orphan*/  callback; int /*<<< orphan*/ * uuid; } ;
struct tbnet {TYPE_1__ handler; int /*<<< orphan*/  napi; struct tb_xdomain* xd; struct net_device* dev; struct tb_service* svc; int /*<<< orphan*/  frame_id; int /*<<< orphan*/  command_id; int /*<<< orphan*/  connection_lock; int /*<<< orphan*/  disconnect_work; int /*<<< orphan*/  connected_work; int /*<<< orphan*/  login_work; } ;
struct tb_xdomain {int dummy; } ;
struct tb_service_id {int dummy; } ;
struct tb_service {int /*<<< orphan*/  dev; } ;
struct net_device {int hw_features; int features; int hard_header_len; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int NETIF_F_ALL_TSO ; 
 int NETIF_F_GRO ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ TBNET_MAX_MTU ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct tbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tb_register_protocol_handler (TYPE_1__*) ; 
 struct tb_xdomain* tb_service_parent (struct tb_service*) ; 
 int /*<<< orphan*/  tb_service_set_drvdata (struct tb_service*,struct tbnet*) ; 
 int /*<<< orphan*/  tb_unregister_protocol_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  tbnet_connected_work ; 
 int /*<<< orphan*/  tbnet_disconnect_work ; 
 int /*<<< orphan*/  tbnet_generate_mac (struct net_device*) ; 
 int /*<<< orphan*/  tbnet_handle_packet ; 
 int /*<<< orphan*/  tbnet_login_work ; 
 int /*<<< orphan*/  tbnet_netdev_ops ; 
 int /*<<< orphan*/  tbnet_poll ; 
 int /*<<< orphan*/  tbnet_svc_uuid ; 

__attribute__((used)) static int tbnet_probe(struct tb_service *svc, const struct tb_service_id *id)
{
	struct tb_xdomain *xd = tb_service_parent(svc);
	struct net_device *dev;
	struct tbnet *net;
	int ret;

	dev = alloc_etherdev(sizeof(*net));
	if (!dev)
		return -ENOMEM;

	SET_NETDEV_DEV(dev, &svc->dev);

	net = netdev_priv(dev);
	INIT_DELAYED_WORK(&net->login_work, tbnet_login_work);
	INIT_WORK(&net->connected_work, tbnet_connected_work);
	INIT_WORK(&net->disconnect_work, tbnet_disconnect_work);
	mutex_init(&net->connection_lock);
	atomic_set(&net->command_id, 0);
	atomic_set(&net->frame_id, 0);
	net->svc = svc;
	net->dev = dev;
	net->xd = xd;

	tbnet_generate_mac(dev);

	strcpy(dev->name, "thunderbolt%d");
	dev->netdev_ops = &tbnet_netdev_ops;

	/* ThunderboltIP takes advantage of TSO packets but instead of
	 * segmenting them we just split the packet into Thunderbolt
	 * frames (maximum payload size of each frame is 4084 bytes) and
	 * calculate checksum over the whole packet here.
	 *
	 * The receiving side does the opposite if the host OS supports
	 * LRO, otherwise it needs to split the large packet into MTU
	 * sized smaller packets.
	 *
	 * In order to receive large packets from the networking stack,
	 * we need to announce support for most of the offloading
	 * features here.
	 */
	dev->hw_features = NETIF_F_SG | NETIF_F_ALL_TSO | NETIF_F_GRO |
			   NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	dev->features = dev->hw_features | NETIF_F_HIGHDMA;
	dev->hard_header_len += sizeof(struct thunderbolt_ip_frame_header);

	netif_napi_add(dev, &net->napi, tbnet_poll, NAPI_POLL_WEIGHT);

	/* MTU range: 68 - 65522 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = TBNET_MAX_MTU - ETH_HLEN;

	net->handler.uuid = &tbnet_svc_uuid;
	net->handler.callback = tbnet_handle_packet,
	net->handler.data = net;
	tb_register_protocol_handler(&net->handler);

	tb_service_set_drvdata(svc, net);

	ret = register_netdev(dev);
	if (ret) {
		tb_unregister_protocol_handler(&net->handler);
		free_netdev(dev);
		return ret;
	}

	return 0;
}