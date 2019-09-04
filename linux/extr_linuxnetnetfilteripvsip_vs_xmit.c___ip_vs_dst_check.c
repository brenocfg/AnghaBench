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
struct ip_vs_dest_dst {int /*<<< orphan*/  dst_cookie; struct dst_entry* dst_cache; } ;
struct ip_vs_dest {int /*<<< orphan*/  dest_dst; } ;
struct dst_entry {TYPE_1__* ops; scalar_t__ obsolete; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct ip_vs_dest_dst* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ip_vs_dest_dst *
__ip_vs_dst_check(struct ip_vs_dest *dest)
{
	struct ip_vs_dest_dst *dest_dst = rcu_dereference(dest->dest_dst);
	struct dst_entry *dst;

	if (!dest_dst)
		return NULL;
	dst = dest_dst->dst_cache;
	if (dst->obsolete &&
	    dst->ops->check(dst, dest_dst->dst_cookie) == NULL)
		return NULL;
	return dest_dst;
}