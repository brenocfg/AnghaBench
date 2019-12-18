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
struct xdp_sock {int /*<<< orphan*/  queue_id; TYPE_1__* dev; } ;
struct xdp_diag_info {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  ifindex; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  di ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDP_DIAG_INFO ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct xdp_diag_info*) ; 

__attribute__((used)) static int xsk_diag_put_info(const struct xdp_sock *xs, struct sk_buff *nlskb)
{
	struct xdp_diag_info di = {};

	di.ifindex = xs->dev ? xs->dev->ifindex : 0;
	di.queue_id = xs->queue_id;
	return nla_put(nlskb, XDP_DIAG_INFO, sizeof(di), &di);
}