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
struct sk_buff {int len; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct dn_zone {int /*<<< orphan*/  dz_order; } ;
struct dn_fib_table {int /*<<< orphan*/  n; } ;
struct dn_fib_node {int fn_state; int /*<<< orphan*/  fn_info; int /*<<< orphan*/  fn_key; int /*<<< orphan*/  fn_scope; int /*<<< orphan*/  fn_type; struct dn_fib_node* fn_next; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int DN_S_ZOMBIE ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 scalar_t__ dn_fib_dump_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int dn_hash_dump_bucket(struct sk_buff *skb,
				struct netlink_callback *cb,
				struct dn_fib_table *tb,
				struct dn_zone *dz,
				struct dn_fib_node *f)
{
	int i, s_i;

	s_i = cb->args[4];
	for(i = 0; f; i++, f = f->fn_next) {
		if (i < s_i)
			continue;
		if (f->fn_state & DN_S_ZOMBIE)
			continue;
		if (dn_fib_dump_info(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq,
				RTM_NEWROUTE,
				tb->n,
				(f->fn_state & DN_S_ZOMBIE) ? 0 : f->fn_type,
				f->fn_scope, &f->fn_key, dz->dz_order,
				f->fn_info, NLM_F_MULTI) < 0) {
			cb->args[4] = i;
			return -1;
		}
	}
	cb->args[4] = i;
	return skb->len;
}