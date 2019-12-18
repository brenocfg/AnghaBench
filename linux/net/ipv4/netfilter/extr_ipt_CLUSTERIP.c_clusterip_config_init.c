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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct ipt_clusterip_tgt_info {int /*<<< orphan*/  hash_initval; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  num_total_nodes; int /*<<< orphan*/  clustermac; } ;
struct clusterip_net {int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  procdir; int /*<<< orphan*/  configs; } ;
struct clusterip_config {int /*<<< orphan*/  list; int /*<<< orphan*/  entries; int /*<<< orphan*/  pde; int /*<<< orphan*/  refcount; struct net* net; int /*<<< orphan*/  hash_initval; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  num_total_nodes; int /*<<< orphan*/  clusterip; int /*<<< orphan*/  clustermac; int /*<<< orphan*/  ifname; int /*<<< orphan*/  ifindex; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct clusterip_config* ERR_PTR (int) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ __clusterip_config_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterip_config_init_nodelist (struct clusterip_config*,struct ipt_clusterip_tgt_info const*) ; 
 int /*<<< orphan*/  clusterip_config_put (struct clusterip_config*) ; 
 struct clusterip_net* clusterip_pernet (struct net*) ; 
 int /*<<< orphan*/  clusterip_proc_fops ; 
 struct net_device* dev_get_by_name (struct net*,char const*) ; 
 int /*<<< orphan*/  dev_mc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct clusterip_config*) ; 
 struct clusterip_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  proc_create_data (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct clusterip_config*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clusterip_config *
clusterip_config_init(struct net *net, const struct ipt_clusterip_tgt_info *i,
		      __be32 ip, const char *iniface)
{
	struct clusterip_net *cn = clusterip_pernet(net);
	struct clusterip_config *c;
	struct net_device *dev;
	int err;

	if (iniface[0] == '\0') {
		pr_info("Please specify an interface name\n");
		return ERR_PTR(-EINVAL);
	}

	c = kzalloc(sizeof(*c), GFP_ATOMIC);
	if (!c)
		return ERR_PTR(-ENOMEM);

	dev = dev_get_by_name(net, iniface);
	if (!dev) {
		pr_info("no such interface %s\n", iniface);
		kfree(c);
		return ERR_PTR(-ENOENT);
	}
	c->ifindex = dev->ifindex;
	strcpy(c->ifname, dev->name);
	memcpy(&c->clustermac, &i->clustermac, ETH_ALEN);
	dev_mc_add(dev, c->clustermac);
	dev_put(dev);

	c->clusterip = ip;
	c->num_total_nodes = i->num_total_nodes;
	clusterip_config_init_nodelist(c, i);
	c->hash_mode = i->hash_mode;
	c->hash_initval = i->hash_initval;
	c->net = net;
	refcount_set(&c->refcount, 1);

	spin_lock_bh(&cn->lock);
	if (__clusterip_config_find(net, ip)) {
		err = -EBUSY;
		goto out_config_put;
	}

	list_add_rcu(&c->list, &cn->configs);
	spin_unlock_bh(&cn->lock);

#ifdef CONFIG_PROC_FS
	{
		char buffer[16];

		/* create proc dir entry */
		sprintf(buffer, "%pI4", &ip);
		mutex_lock(&cn->mutex);
		c->pde = proc_create_data(buffer, 0600,
					  cn->procdir,
					  &clusterip_proc_fops, c);
		mutex_unlock(&cn->mutex);
		if (!c->pde) {
			err = -ENOMEM;
			goto err;
		}
	}
#endif

	refcount_set(&c->entries, 1);
	return c;

#ifdef CONFIG_PROC_FS
err:
#endif
	spin_lock_bh(&cn->lock);
	list_del_rcu(&c->list);
out_config_put:
	spin_unlock_bh(&cn->lock);
	clusterip_config_put(c);
	return ERR_PTR(err);
}