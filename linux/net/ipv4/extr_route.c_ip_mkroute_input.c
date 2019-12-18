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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct in_device {int dummy; } ;
struct flow_keys {int dummy; } ;
struct fib_result {TYPE_1__* fi; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  fib_net; } ;

/* Variables and functions */
 int __mkroute_input (struct sk_buff*,struct fib_result*,struct in_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fib_info_num_path (TYPE_1__*) ; 
 int fib_multipath_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  fib_select_multipath (struct fib_result*,int) ; 

__attribute__((used)) static int ip_mkroute_input(struct sk_buff *skb,
			    struct fib_result *res,
			    struct in_device *in_dev,
			    __be32 daddr, __be32 saddr, u32 tos,
			    struct flow_keys *hkeys)
{
#ifdef CONFIG_IP_ROUTE_MULTIPATH
	if (res->fi && fib_info_num_path(res->fi) > 1) {
		int h = fib_multipath_hash(res->fi->fib_net, NULL, skb, hkeys);

		fib_select_multipath(res, h);
	}
#endif

	/* create a routing cache entry */
	return __mkroute_input(skb, res, in_dev, daddr, saddr, tos);
}