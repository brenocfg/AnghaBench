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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {struct tb_ring* ring; } ;
struct TYPE_5__ {struct tb_ring* ring; } ;
struct tbnet {int /*<<< orphan*/  napi; TYPE_3__ rx_ring; TYPE_2__ tx_ring; struct tb_xdomain* xd; } ;
struct tb_xdomain {TYPE_1__* tb; } ;
struct tb_ring {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nhi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int RING_FLAG_E2E ; 
 int RING_FLAG_FRAME ; 
 int /*<<< orphan*/  TBIP_PDF_FRAME_END ; 
 int /*<<< orphan*/  TBIP_PDF_FRAME_START ; 
 int /*<<< orphan*/  TBNET_RING_SIZE ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct tbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  start_login (struct tbnet*) ; 
 struct tb_ring* tb_ring_alloc_rx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tbnet*) ; 
 struct tb_ring* tb_ring_alloc_tx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_ring_free (struct tb_ring*) ; 
 int /*<<< orphan*/  tbnet_start_poll ; 

__attribute__((used)) static int tbnet_open(struct net_device *dev)
{
	struct tbnet *net = netdev_priv(dev);
	struct tb_xdomain *xd = net->xd;
	u16 sof_mask, eof_mask;
	struct tb_ring *ring;

	netif_carrier_off(dev);

	ring = tb_ring_alloc_tx(xd->tb->nhi, -1, TBNET_RING_SIZE,
				RING_FLAG_FRAME);
	if (!ring) {
		netdev_err(dev, "failed to allocate Tx ring\n");
		return -ENOMEM;
	}
	net->tx_ring.ring = ring;

	sof_mask = BIT(TBIP_PDF_FRAME_START);
	eof_mask = BIT(TBIP_PDF_FRAME_END);

	ring = tb_ring_alloc_rx(xd->tb->nhi, -1, TBNET_RING_SIZE,
				RING_FLAG_FRAME | RING_FLAG_E2E, sof_mask,
				eof_mask, tbnet_start_poll, net);
	if (!ring) {
		netdev_err(dev, "failed to allocate Rx ring\n");
		tb_ring_free(net->tx_ring.ring);
		net->tx_ring.ring = NULL;
		return -ENOMEM;
	}
	net->rx_ring.ring = ring;

	napi_enable(&net->napi);
	start_login(net);

	return 0;
}