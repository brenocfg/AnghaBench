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
typedef  int /*<<< orphan*/  xdp ;
typedef  int /*<<< orphan*/  u32 ;
struct netdev_bpf {int command; int /*<<< orphan*/  prog_id; } ;
struct net_device {int dummy; } ;
typedef  enum bpf_netdev_command { ____Placeholder_bpf_netdev_command } bpf_netdev_command ;
typedef  scalar_t__ (* bpf_op_t ) (struct net_device*,struct netdev_bpf*) ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int XDP_QUERY_PROG ; 
 int /*<<< orphan*/  memset (struct netdev_bpf*,int /*<<< orphan*/ ,int) ; 

u32 __dev_xdp_query(struct net_device *dev, bpf_op_t bpf_op,
		    enum bpf_netdev_command cmd)
{
	struct netdev_bpf xdp;

	if (!bpf_op)
		return 0;

	memset(&xdp, 0, sizeof(xdp));
	xdp.command = cmd;

	/* Query must always succeed. */
	WARN_ON(bpf_op(dev, &xdp) < 0 && cmd == XDP_QUERY_PROG);

	return xdp.prog_id;
}