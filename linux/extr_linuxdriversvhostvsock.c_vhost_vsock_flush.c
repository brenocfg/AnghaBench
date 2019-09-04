#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vhost_vsock {int /*<<< orphan*/  send_pkt_work; int /*<<< orphan*/  dev; TYPE_1__* vqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll; scalar_t__ handle_kick; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_poll_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_work_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_vsock_flush(struct vhost_vsock *vsock)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vsock->vqs); i++)
		if (vsock->vqs[i].handle_kick)
			vhost_poll_flush(&vsock->vqs[i].poll);
	vhost_work_flush(&vsock->dev, &vsock->send_pkt_work);
}