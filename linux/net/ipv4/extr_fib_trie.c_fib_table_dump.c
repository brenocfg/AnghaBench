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
typedef  void* t_key ;
struct trie {struct key_vector* kv; } ;
struct sk_buff {int len; } ;
struct netlink_callback {int* args; } ;
struct key_vector {void* key; } ;
struct fib_table {scalar_t__ tb_data; } ;
struct fib_dump_filter {int dummy; } ;

/* Variables and functions */
 int fn_trie_dump_leaf (struct key_vector*,struct fib_table*,struct sk_buff*,struct netlink_callback*,struct fib_dump_filter*) ; 
 struct key_vector* leaf_walk_rcu (struct key_vector**,void*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int fib_table_dump(struct fib_table *tb, struct sk_buff *skb,
		   struct netlink_callback *cb, struct fib_dump_filter *filter)
{
	struct trie *t = (struct trie *)tb->tb_data;
	struct key_vector *l, *tp = t->kv;
	/* Dump starting at last key.
	 * Note: 0.0.0.0/0 (ie default) is first key.
	 */
	int count = cb->args[2];
	t_key key = cb->args[3];

	while ((l = leaf_walk_rcu(&tp, key)) != NULL) {
		int err;

		err = fn_trie_dump_leaf(l, tb, skb, cb, filter);
		if (err < 0) {
			cb->args[3] = key;
			cb->args[2] = count;
			return err;
		}

		++count;
		key = l->key + 1;

		memset(&cb->args[4], 0,
		       sizeof(cb->args) - 4*sizeof(cb->args[0]));

		/* stop loop if key wrapped back to 0 */
		if (key < l->key)
			break;
	}

	cb->args[3] = key;
	cb->args[2] = count;

	return skb->len;
}