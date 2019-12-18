#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rt6i_uncached_list; int /*<<< orphan*/  rt6i_idev; } ;
struct TYPE_3__ {TYPE_2__ rt6; } ;
struct xfrm_dst {TYPE_1__ u; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_destroy_metrics_generic (struct dst_entry*) ; 
 int /*<<< orphan*/  in6_dev_put (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt6_uncached_list_del (TYPE_2__*) ; 
 int /*<<< orphan*/  xfrm_dst_destroy (struct xfrm_dst*) ; 

__attribute__((used)) static void xfrm6_dst_destroy(struct dst_entry *dst)
{
	struct xfrm_dst *xdst = (struct xfrm_dst *)dst;

	if (likely(xdst->u.rt6.rt6i_idev))
		in6_dev_put(xdst->u.rt6.rt6i_idev);
	dst_destroy_metrics_generic(dst);
	if (xdst->u.rt6.rt6i_uncached_list)
		rt6_uncached_list_del(&xdst->u.rt6);
	xfrm_dst_destroy(xdst);
}