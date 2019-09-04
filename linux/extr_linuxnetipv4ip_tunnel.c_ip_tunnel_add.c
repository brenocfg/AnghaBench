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
struct ip_tunnel {int /*<<< orphan*/  hash_node; scalar_t__ collect_md; int /*<<< orphan*/  parms; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct hlist_head* ip_bucket (struct ip_tunnel_net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ip_tunnel*) ; 

__attribute__((used)) static void ip_tunnel_add(struct ip_tunnel_net *itn, struct ip_tunnel *t)
{
	struct hlist_head *head = ip_bucket(itn, &t->parms);

	if (t->collect_md)
		rcu_assign_pointer(itn->collect_md_tun, t);
	hlist_add_head_rcu(&t->hash_node, head);
}