#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct serdev_device {int dummy; } ;
struct qcauart {TYPE_1__* rx_skb; int /*<<< orphan*/  frm_handle; struct net_device* net_dev; } ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {scalar_t__ mtu; struct net_device_stats stats; } ;
typedef  int s32 ;
struct TYPE_5__ {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
#define  QCAFRM_GATHER 131 
#define  QCAFRM_INVLEN 130 
#define  QCAFRM_NOHEAD 129 
#define  QCAFRM_NOTAIL 128 
 scalar_t__ VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  eth_type_trans (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* netdev_alloc_skb_ip_align (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_rx_ni (TYPE_1__*) ; 
 int qcafrm_fsm_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const) ; 
 struct qcauart* serdev_device_get_drvdata (struct serdev_device*) ; 
 int /*<<< orphan*/  skb_put (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_tailroom (TYPE_1__*) ; 

__attribute__((used)) static int
qca_tty_receive(struct serdev_device *serdev, const unsigned char *data,
		size_t count)
{
	struct qcauart *qca = serdev_device_get_drvdata(serdev);
	struct net_device *netdev = qca->net_dev;
	struct net_device_stats *n_stats = &netdev->stats;
	size_t i;

	if (!qca->rx_skb) {
		qca->rx_skb = netdev_alloc_skb_ip_align(netdev,
							netdev->mtu +
							VLAN_ETH_HLEN);
		if (!qca->rx_skb) {
			n_stats->rx_errors++;
			n_stats->rx_dropped++;
			return 0;
		}
	}

	for (i = 0; i < count; i++) {
		s32 retcode;

		retcode = qcafrm_fsm_decode(&qca->frm_handle,
					    qca->rx_skb->data,
					    skb_tailroom(qca->rx_skb),
					    data[i]);

		switch (retcode) {
		case QCAFRM_GATHER:
		case QCAFRM_NOHEAD:
			break;
		case QCAFRM_NOTAIL:
			netdev_dbg(netdev, "recv: no RX tail\n");
			n_stats->rx_errors++;
			n_stats->rx_dropped++;
			break;
		case QCAFRM_INVLEN:
			netdev_dbg(netdev, "recv: invalid RX length\n");
			n_stats->rx_errors++;
			n_stats->rx_dropped++;
			break;
		default:
			n_stats->rx_packets++;
			n_stats->rx_bytes += retcode;
			skb_put(qca->rx_skb, retcode);
			qca->rx_skb->protocol = eth_type_trans(
						qca->rx_skb, qca->rx_skb->dev);
			qca->rx_skb->ip_summed = CHECKSUM_UNNECESSARY;
			netif_rx_ni(qca->rx_skb);
			qca->rx_skb = netdev_alloc_skb_ip_align(netdev,
								netdev->mtu +
								VLAN_ETH_HLEN);
			if (!qca->rx_skb) {
				netdev_dbg(netdev, "recv: out of RX resources\n");
				n_stats->rx_errors++;
				return i;
			}
		}
	}

	return i;
}