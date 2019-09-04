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
struct virtio_rpmsg_channel {int /*<<< orphan*/  vrp; } ;
struct rpmsg_endpoint {int /*<<< orphan*/  rpdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpmsg_destroy_ept (int /*<<< orphan*/ ,struct rpmsg_endpoint*) ; 
 struct virtio_rpmsg_channel* to_virtio_rpmsg_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtio_rpmsg_destroy_ept(struct rpmsg_endpoint *ept)
{
	struct virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(ept->rpdev);

	__rpmsg_destroy_ept(vch->vrp, ept);
}