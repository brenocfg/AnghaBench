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
struct vhost_net_buf {size_t tail; size_t head; void** queue; } ;

/* Variables and functions */

__attribute__((used)) static void *vhost_net_buf_get_ptr(struct vhost_net_buf *rxq)
{
	if (rxq->tail != rxq->head)
		return rxq->queue[rxq->head];
	else
		return NULL;
}