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
typedef  int /*<<< orphan*/  u32 ;
struct ip_vs_dest_dst {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  dst_cookie; struct dst_entry* dst_cache; } ;
struct ip_vs_dest {int /*<<< orphan*/  dest_dst; int /*<<< orphan*/  dst_lock; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_dest_dst_rcu_free ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ip_vs_dest_dst*) ; 
 struct ip_vs_dest_dst* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
__ip_vs_dst_set(struct ip_vs_dest *dest, struct ip_vs_dest_dst *dest_dst,
		struct dst_entry *dst, u32 dst_cookie)
{
	struct ip_vs_dest_dst *old;

	old = rcu_dereference_protected(dest->dest_dst,
					lockdep_is_held(&dest->dst_lock));

	if (dest_dst) {
		dest_dst->dst_cache = dst;
		dest_dst->dst_cookie = dst_cookie;
	}
	rcu_assign_pointer(dest->dest_dst, dest_dst);

	if (old)
		call_rcu(&old->rcu_head, ip_vs_dest_dst_rcu_free);
}