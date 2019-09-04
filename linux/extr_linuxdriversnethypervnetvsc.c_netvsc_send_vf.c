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
struct TYPE_4__ {int /*<<< orphan*/  serial; scalar_t__ allocated; } ;
struct TYPE_5__ {TYPE_1__ vf_assoc; } ;
struct TYPE_6__ {TYPE_2__ v4_msg; } ;
struct nvsp_message {TYPE_3__ msg; } ;
struct net_device_context {scalar_t__ vf_alloc; int /*<<< orphan*/  vf_serial; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,char*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netvsc_send_vf(struct net_device *ndev,
			   const struct nvsp_message *nvmsg)
{
	struct net_device_context *net_device_ctx = netdev_priv(ndev);

	net_device_ctx->vf_alloc = nvmsg->msg.v4_msg.vf_assoc.allocated;
	net_device_ctx->vf_serial = nvmsg->msg.v4_msg.vf_assoc.serial;
	netdev_info(ndev, "VF slot %u %s\n",
		    net_device_ctx->vf_serial,
		    net_device_ctx->vf_alloc ? "added" : "removed");
}