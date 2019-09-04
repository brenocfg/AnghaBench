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
struct ip_vs_dest_dst {int /*<<< orphan*/  rcu_head; } ;
struct ip_vs_dest {int /*<<< orphan*/  dest_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_dest_dst_rcu_free ; 
 struct ip_vs_dest_dst* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __ip_vs_dst_cache_reset(struct ip_vs_dest *dest)
{
	struct ip_vs_dest_dst *old;

	old = rcu_dereference_protected(dest->dest_dst, 1);
	if (old) {
		RCU_INIT_POINTER(dest->dest_dst, NULL);
		call_rcu(&old->rcu_head, ip_vs_dest_dst_rcu_free);
	}
}