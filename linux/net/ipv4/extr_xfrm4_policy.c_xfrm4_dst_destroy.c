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
struct TYPE_4__ {scalar_t__ rt_uncached_list; } ;
struct TYPE_3__ {TYPE_2__ rt; } ;
struct xfrm_dst {TYPE_1__ u; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_destroy_metrics_generic (struct dst_entry*) ; 
 int /*<<< orphan*/  rt_del_uncached_list (TYPE_2__*) ; 
 int /*<<< orphan*/  xfrm_dst_destroy (struct xfrm_dst*) ; 

__attribute__((used)) static void xfrm4_dst_destroy(struct dst_entry *dst)
{
	struct xfrm_dst *xdst = (struct xfrm_dst *)dst;

	dst_destroy_metrics_generic(dst);
	if (xdst->u.rt.rt_uncached_list)
		rt_del_uncached_list(&xdst->u.rt);
	xfrm_dst_destroy(xdst);
}