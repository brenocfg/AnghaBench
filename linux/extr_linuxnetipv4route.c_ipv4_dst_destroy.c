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
struct rtable {int dummy; } ;
struct dst_metrics {int /*<<< orphan*/  refcnt; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ DST_METRICS_PTR (struct dst_entry*) ; 
 struct dst_metrics dst_default_metrics ; 
 int /*<<< orphan*/  kfree (struct dst_metrics*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_del_uncached_list (struct rtable*) ; 

__attribute__((used)) static void ipv4_dst_destroy(struct dst_entry *dst)
{
	struct dst_metrics *p = (struct dst_metrics *)DST_METRICS_PTR(dst);
	struct rtable *rt = (struct rtable *)dst;

	if (p != &dst_default_metrics && refcount_dec_and_test(&p->refcnt))
		kfree(p);

	rt_del_uncached_list(rt);
}