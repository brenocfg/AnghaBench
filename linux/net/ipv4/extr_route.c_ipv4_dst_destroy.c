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
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_dst_metrics_put (struct dst_entry*) ; 
 int /*<<< orphan*/  rt_del_uncached_list (struct rtable*) ; 

__attribute__((used)) static void ipv4_dst_destroy(struct dst_entry *dst)
{
	struct rtable *rt = (struct rtable *)dst;

	ip_dst_metrics_put(dst);
	rt_del_uncached_list(rt);
}