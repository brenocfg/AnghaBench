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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct dst_metrics {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  metrics; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dst_metrics* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dst_default_metrics ; 
 int ip_metrics_convert (struct net*,struct nlattr*,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  kfree (struct dst_metrics*) ; 
 struct dst_metrics* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

struct dst_metrics *ip_fib_metrics_init(struct net *net, struct nlattr *fc_mx,
					int fc_mx_len,
					struct netlink_ext_ack *extack)
{
	struct dst_metrics *fib_metrics;
	int err;

	if (!fc_mx)
		return (struct dst_metrics *)&dst_default_metrics;

	fib_metrics = kzalloc(sizeof(*fib_metrics), GFP_KERNEL);
	if (unlikely(!fib_metrics))
		return ERR_PTR(-ENOMEM);

	err = ip_metrics_convert(net, fc_mx, fc_mx_len, fib_metrics->metrics,
				 extack);
	if (!err) {
		refcount_set(&fib_metrics->refcnt, 1);
	} else {
		kfree(fib_metrics);
		fib_metrics = ERR_PTR(err);
	}

	return fib_metrics;
}