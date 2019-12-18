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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct neighbour {TYPE_1__* dev; } ;
struct dst_entry {int dummy; } ;
struct dn_route {struct neighbour* n; } ;
struct dn_dev {scalar_t__ use_long; } ;
struct TYPE_2__ {int /*<<< orphan*/  dn_ptr; } ;

/* Variables and functions */
 scalar_t__ DN_MAX_NSP_DATA_HEADER ; 
 int /*<<< orphan*/  RTAX_ADVMSS ; 
 int /*<<< orphan*/  RTAX_MTU ; 
 int /*<<< orphan*/  dn_rt_mtu_expires ; 
 scalar_t__ dst_metric (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_metric_locked (struct dst_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ dst_metric_raw (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_metric_set (struct dst_entry*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dst_set_expires (struct dst_entry*,int /*<<< orphan*/ ) ; 
 struct dn_dev* rcu_dereference_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dn_dst_update_pmtu(struct dst_entry *dst, struct sock *sk,
			       struct sk_buff *skb, u32 mtu)
{
	struct dn_route *rt = (struct dn_route *) dst;
	struct neighbour *n = rt->n;
	u32 min_mtu = 230;
	struct dn_dev *dn;

	dn = n ? rcu_dereference_raw(n->dev->dn_ptr) : NULL;

	if (dn && dn->use_long == 0)
		min_mtu -= 6;
	else
		min_mtu -= 21;

	if (dst_metric(dst, RTAX_MTU) > mtu && mtu >= min_mtu) {
		if (!(dst_metric_locked(dst, RTAX_MTU))) {
			dst_metric_set(dst, RTAX_MTU, mtu);
			dst_set_expires(dst, dn_rt_mtu_expires);
		}
		if (!(dst_metric_locked(dst, RTAX_ADVMSS))) {
			u32 mss = mtu - DN_MAX_NSP_DATA_HEADER;
			u32 existing_mss = dst_metric_raw(dst, RTAX_ADVMSS);
			if (!existing_mss || existing_mss > mss)
				dst_metric_set(dst, RTAX_ADVMSS, mss);
		}
	}
}