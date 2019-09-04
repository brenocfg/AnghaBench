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
struct vhost_virtqueue {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t VHOST_NET_WEIGHT ; 
 int /*<<< orphan*/  vhost_vq_avail_empty (int /*<<< orphan*/ ,struct vhost_virtqueue*) ; 

__attribute__((used)) static bool tx_can_batch(struct vhost_virtqueue *vq, size_t total_len)
{
	return total_len < VHOST_NET_WEIGHT &&
	       !vhost_vq_avail_empty(vq->dev, vq);
}