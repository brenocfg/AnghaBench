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
typedef  int /*<<< orphan*/  u32 ;
struct rpmsg_endpoint {int /*<<< orphan*/  addr; struct rpmsg_device* rpdev; } ;
struct rpmsg_device {int dummy; } ;

/* Variables and functions */
 int rpmsg_send_offchannel_raw (struct rpmsg_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int) ; 

__attribute__((used)) static int virtio_rpmsg_trysendto(struct rpmsg_endpoint *ept, void *data,
				  int len, u32 dst)
{
	struct rpmsg_device *rpdev = ept->rpdev;
	u32 src = ept->addr;

	return rpmsg_send_offchannel_raw(rpdev, src, dst, data, len, false);
}