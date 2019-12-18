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
typedef  size_t u8 ;
struct nf_nat_lookup_hook_priv {unsigned int hooknum; int /*<<< orphan*/  entries; struct nf_nat_lookup_hook_priv* priv; } ;
struct nf_nat_hooks_net {scalar_t__ users; struct nf_nat_lookup_hook_priv* nat_hook_ops; } ;
struct nf_hook_ops {unsigned int hooknum; int /*<<< orphan*/  entries; struct nf_hook_ops* priv; } ;
struct net {int dummy; } ;
struct nat_net {struct nf_nat_hooks_net* nat_proto_net; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct nf_nat_hooks_net*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kfree (struct nf_nat_lookup_hook_priv*) ; 
 struct nf_nat_lookup_hook_priv* kmemdup (struct nf_nat_lookup_hook_priv const*,int,int /*<<< orphan*/ ) ; 
 struct nf_nat_lookup_hook_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat_net_id ; 
 struct nat_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int nf_hook_entries_insert_raw (int /*<<< orphan*/ *,struct nf_nat_lookup_hook_priv const*) ; 
 int /*<<< orphan*/  nf_nat_proto_mutex ; 
 int nf_register_net_hooks (struct net*,struct nf_nat_lookup_hook_priv*,unsigned int) ; 

int nf_nat_register_fn(struct net *net, u8 pf, const struct nf_hook_ops *ops,
		       const struct nf_hook_ops *orig_nat_ops, unsigned int ops_count)
{
	struct nat_net *nat_net = net_generic(net, nat_net_id);
	struct nf_nat_hooks_net *nat_proto_net;
	struct nf_nat_lookup_hook_priv *priv;
	unsigned int hooknum = ops->hooknum;
	struct nf_hook_ops *nat_ops;
	int i, ret;

	if (WARN_ON_ONCE(pf >= ARRAY_SIZE(nat_net->nat_proto_net)))
		return -EINVAL;

	nat_proto_net = &nat_net->nat_proto_net[pf];

	for (i = 0; i < ops_count; i++) {
		if (orig_nat_ops[i].hooknum == hooknum) {
			hooknum = i;
			break;
		}
	}

	if (WARN_ON_ONCE(i == ops_count))
		return -EINVAL;

	mutex_lock(&nf_nat_proto_mutex);
	if (!nat_proto_net->nat_hook_ops) {
		WARN_ON(nat_proto_net->users != 0);

		nat_ops = kmemdup(orig_nat_ops, sizeof(*orig_nat_ops) * ops_count, GFP_KERNEL);
		if (!nat_ops) {
			mutex_unlock(&nf_nat_proto_mutex);
			return -ENOMEM;
		}

		for (i = 0; i < ops_count; i++) {
			priv = kzalloc(sizeof(*priv), GFP_KERNEL);
			if (priv) {
				nat_ops[i].priv = priv;
				continue;
			}
			mutex_unlock(&nf_nat_proto_mutex);
			while (i)
				kfree(nat_ops[--i].priv);
			kfree(nat_ops);
			return -ENOMEM;
		}

		ret = nf_register_net_hooks(net, nat_ops, ops_count);
		if (ret < 0) {
			mutex_unlock(&nf_nat_proto_mutex);
			for (i = 0; i < ops_count; i++)
				kfree(nat_ops[i].priv);
			kfree(nat_ops);
			return ret;
		}

		nat_proto_net->nat_hook_ops = nat_ops;
	}

	nat_ops = nat_proto_net->nat_hook_ops;
	priv = nat_ops[hooknum].priv;
	if (WARN_ON_ONCE(!priv)) {
		mutex_unlock(&nf_nat_proto_mutex);
		return -EOPNOTSUPP;
	}

	ret = nf_hook_entries_insert_raw(&priv->entries, ops);
	if (ret == 0)
		nat_proto_net->users++;

	mutex_unlock(&nf_nat_proto_mutex);
	return ret;
}