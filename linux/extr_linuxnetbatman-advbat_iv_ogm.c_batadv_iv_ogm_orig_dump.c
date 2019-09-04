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
struct sk_buff {int dummy; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct hlist_head {int dummy; } ;
struct batadv_priv {struct batadv_hashtable* orig_hash; } ;
struct batadv_hashtable {int size; struct hlist_head* table; } ;
struct batadv_hard_iface {int dummy; } ;
struct TYPE_4__ {int portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 scalar_t__ batadv_iv_ogm_orig_dump_bucket (struct sk_buff*,int,int /*<<< orphan*/ ,struct batadv_priv*,struct batadv_hard_iface*,struct hlist_head*,int*,int*) ; 

__attribute__((used)) static void
batadv_iv_ogm_orig_dump(struct sk_buff *msg, struct netlink_callback *cb,
			struct batadv_priv *bat_priv,
			struct batadv_hard_iface *if_outgoing)
{
	struct batadv_hashtable *hash = bat_priv->orig_hash;
	struct hlist_head *head;
	int bucket = cb->args[0];
	int idx = cb->args[1];
	int sub = cb->args[2];
	int portid = NETLINK_CB(cb->skb).portid;

	while (bucket < hash->size) {
		head = &hash->table[bucket];

		if (batadv_iv_ogm_orig_dump_bucket(msg, portid,
						   cb->nlh->nlmsg_seq,
						   bat_priv, if_outgoing, head,
						   &idx, &sub))
			break;

		bucket++;
	}

	cb->args[0] = bucket;
	cb->args[1] = idx;
	cb->args[2] = sub;
}