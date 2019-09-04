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
struct rpmsg_endpoint {int dummy; } ;
struct rpmsg_device {TYPE_1__* ops; } ;
struct rpmsg_channel_info {int dummy; } ;
typedef  int /*<<< orphan*/  rpmsg_rx_cb_t ;
struct TYPE_2__ {struct rpmsg_endpoint* (* create_ept ) (struct rpmsg_device*,int /*<<< orphan*/ ,void*,struct rpmsg_channel_info) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct rpmsg_endpoint* stub1 (struct rpmsg_device*,int /*<<< orphan*/ ,void*,struct rpmsg_channel_info) ; 

struct rpmsg_endpoint *rpmsg_create_ept(struct rpmsg_device *rpdev,
					rpmsg_rx_cb_t cb, void *priv,
					struct rpmsg_channel_info chinfo)
{
	if (WARN_ON(!rpdev))
		return NULL;

	return rpdev->ops->create_ept(rpdev, cb, priv, chinfo);
}