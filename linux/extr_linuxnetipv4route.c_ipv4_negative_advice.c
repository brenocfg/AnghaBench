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
struct TYPE_2__ {scalar_t__ expires; } ;
struct rtable {int rt_flags; TYPE_1__ dst; } ;
struct dst_entry {scalar_t__ obsolete; } ;

/* Variables and functions */
 int RTCF_REDIRECTED ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 

__attribute__((used)) static struct dst_entry *ipv4_negative_advice(struct dst_entry *dst)
{
	struct rtable *rt = (struct rtable *)dst;
	struct dst_entry *ret = dst;

	if (rt) {
		if (dst->obsolete > 0) {
			ip_rt_put(rt);
			ret = NULL;
		} else if ((rt->rt_flags & RTCF_REDIRECTED) ||
			   rt->dst.expires) {
			ip_rt_put(rt);
			ret = NULL;
		}
	}
	return ret;
}