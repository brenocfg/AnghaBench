#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {TYPE_1__* vdev; } ;
struct virtnet_info {int /*<<< orphan*/  dev; TYPE_2__* sq; } ;
struct napi_struct {scalar_t__ weight; } ;
struct TYPE_4__ {struct napi_struct napi; } ;
struct TYPE_3__ {struct virtnet_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_napi_schedule (struct napi_struct*,struct virtqueue*) ; 
 size_t vq2txq (struct virtqueue*) ; 

__attribute__((used)) static void skb_xmit_done(struct virtqueue *vq)
{
	struct virtnet_info *vi = vq->vdev->priv;
	struct napi_struct *napi = &vi->sq[vq2txq(vq)].napi;

	/* Suppress further interrupts. */
	virtqueue_disable_cb(vq);

	if (napi->weight)
		virtqueue_napi_schedule(napi, vq);
	else
		/* We were probably waiting for more output buffers. */
		netif_wake_subqueue(vi->dev, vq2txq(vq));
}