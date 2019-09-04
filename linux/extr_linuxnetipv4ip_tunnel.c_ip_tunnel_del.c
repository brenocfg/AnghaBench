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
struct ip_tunnel_net {int /*<<< orphan*/  collect_md_tun; } ;
struct ip_tunnel {int /*<<< orphan*/  hash_node; scalar_t__ collect_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip_tunnel_del(struct ip_tunnel_net *itn, struct ip_tunnel *t)
{
	if (t->collect_md)
		rcu_assign_pointer(itn->collect_md_tun, NULL);
	hlist_del_init_rcu(&t->hash_node);
}