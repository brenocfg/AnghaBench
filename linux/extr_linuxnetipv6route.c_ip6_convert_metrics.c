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
struct net {int dummy; } ;
struct fib6_info {struct dst_metrics* fib6_metrics; } ;
struct fib6_config {int /*<<< orphan*/  fc_mx_len; int /*<<< orphan*/  fc_mx; } ;
struct dst_metrics {int /*<<< orphan*/  metrics; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ip_metrics_convert (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dst_metrics* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip6_convert_metrics(struct net *net, struct fib6_info *rt,
			       struct fib6_config *cfg)
{
	struct dst_metrics *p;

	if (!cfg->fc_mx)
		return 0;

	p = kzalloc(sizeof(*rt->fib6_metrics), GFP_KERNEL);
	if (unlikely(!p))
		return -ENOMEM;

	refcount_set(&p->refcnt, 1);
	rt->fib6_metrics = p;

	return ip_metrics_convert(net, cfg->fc_mx, cfg->fc_mx_len, p->metrics);
}