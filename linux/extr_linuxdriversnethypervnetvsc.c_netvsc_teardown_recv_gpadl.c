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
struct netvsc_device {scalar_t__ recv_buf_gpadl_handle; } ;
struct net_device {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int vmbus_teardown_gpadl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void netvsc_teardown_recv_gpadl(struct hv_device *device,
				       struct netvsc_device *net_device,
				       struct net_device *ndev)
{
	int ret;

	if (net_device->recv_buf_gpadl_handle) {
		ret = vmbus_teardown_gpadl(device->channel,
					   net_device->recv_buf_gpadl_handle);

		/* If we failed here, we might as well return and have a leak
		 * rather than continue and a bugchk
		 */
		if (ret != 0) {
			netdev_err(ndev,
				   "unable to teardown receive buffer's gpadl\n");
			return;
		}
		net_device->recv_buf_gpadl_handle = 0;
	}
}