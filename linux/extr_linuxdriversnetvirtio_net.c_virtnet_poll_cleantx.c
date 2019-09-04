#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct virtnet_info {int /*<<< orphan*/  dev; struct send_queue* sq; } ;
struct TYPE_5__ {int /*<<< orphan*/  weight; } ;
struct send_queue {TYPE_2__* vq; TYPE_1__ napi; } ;
struct receive_queue {TYPE_4__* vq; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_8__ {TYPE_3__* vdev; } ;
struct TYPE_7__ {struct virtnet_info* priv; } ;
struct TYPE_6__ {scalar_t__ num_free; } ;

/* Variables and functions */
 scalar_t__ MAX_SKB_FRAGS ; 
 scalar_t__ __netif_tx_trylock (struct netdev_queue*) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 int /*<<< orphan*/  free_old_xmit_skbs (struct send_queue*,int) ; 
 scalar_t__ is_xdp_raw_buffer_queue (struct virtnet_info*,unsigned int) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 unsigned int vq2rxq (TYPE_4__*) ; 

__attribute__((used)) static void virtnet_poll_cleantx(struct receive_queue *rq)
{
	struct virtnet_info *vi = rq->vq->vdev->priv;
	unsigned int index = vq2rxq(rq->vq);
	struct send_queue *sq = &vi->sq[index];
	struct netdev_queue *txq = netdev_get_tx_queue(vi->dev, index);

	if (!sq->napi.weight || is_xdp_raw_buffer_queue(vi, index))
		return;

	if (__netif_tx_trylock(txq)) {
		free_old_xmit_skbs(sq, true);
		__netif_tx_unlock(txq);
	}

	if (sq->vq->num_free >= 2 + MAX_SKB_FRAGS)
		netif_tx_wake_queue(txq);
}