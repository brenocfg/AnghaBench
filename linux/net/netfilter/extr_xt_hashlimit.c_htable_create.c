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
typedef  scalar_t__ u_int8_t ;
struct TYPE_2__ {unsigned int size; int max; int /*<<< orphan*/  gc_interval; } ;
struct xt_hashlimit_htable {int use; int rnd_initialized; int /*<<< orphan*/  node; TYPE_1__ cfg; int /*<<< orphan*/  gc_work; struct net* net; int /*<<< orphan*/  name; int /*<<< orphan*/ * pde; int /*<<< orphan*/  lock; scalar_t__ family; scalar_t__ count; int /*<<< orphan*/ * hash; } ;
struct seq_operations {int dummy; } ;
struct net {int dummy; } ;
struct hlist_head {int dummy; } ;
struct hashlimit_net {int /*<<< orphan*/  htables; int /*<<< orphan*/  ip6t_hashlimit; int /*<<< orphan*/  ipt_hashlimit; } ;
struct hashlimit_cfg3 {int size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NFPROTO_IPV4 ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int cfg_copy (TYPE_1__*,void*,int) ; 
 struct seq_operations dl_seq_ops ; 
 struct seq_operations dl_seq_ops_v1 ; 
 struct seq_operations dl_seq_ops_v2 ; 
 int /*<<< orphan*/  hash ; 
 struct hashlimit_net* hashlimit_pernet (struct net*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htable_gc ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_create_seq_data (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct seq_operations const*,struct xt_hashlimit_htable*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct xt_hashlimit_htable*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 unsigned long totalram_pages () ; 
 int /*<<< orphan*/  vfree (struct xt_hashlimit_htable*) ; 
 struct xt_hashlimit_htable* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int htable_create(struct net *net, struct hashlimit_cfg3 *cfg,
			 const char *name, u_int8_t family,
			 struct xt_hashlimit_htable **out_hinfo,
			 int revision)
{
	struct hashlimit_net *hashlimit_net = hashlimit_pernet(net);
	struct xt_hashlimit_htable *hinfo;
	const struct seq_operations *ops;
	unsigned int size, i;
	unsigned long nr_pages = totalram_pages();
	int ret;

	if (cfg->size) {
		size = cfg->size;
	} else {
		size = (nr_pages << PAGE_SHIFT) / 16384 /
		       sizeof(struct hlist_head);
		if (nr_pages > 1024 * 1024 * 1024 / PAGE_SIZE)
			size = 8192;
		if (size < 16)
			size = 16;
	}
	/* FIXME: don't use vmalloc() here or anywhere else -HW */
	hinfo = vmalloc(struct_size(hinfo, hash, size));
	if (hinfo == NULL)
		return -ENOMEM;
	*out_hinfo = hinfo;

	/* copy match config into hashtable config */
	ret = cfg_copy(&hinfo->cfg, (void *)cfg, 3);
	if (ret) {
		vfree(hinfo);
		return ret;
	}

	hinfo->cfg.size = size;
	if (hinfo->cfg.max == 0)
		hinfo->cfg.max = 8 * hinfo->cfg.size;
	else if (hinfo->cfg.max < hinfo->cfg.size)
		hinfo->cfg.max = hinfo->cfg.size;

	for (i = 0; i < hinfo->cfg.size; i++)
		INIT_HLIST_HEAD(&hinfo->hash[i]);

	hinfo->use = 1;
	hinfo->count = 0;
	hinfo->family = family;
	hinfo->rnd_initialized = false;
	hinfo->name = kstrdup(name, GFP_KERNEL);
	if (!hinfo->name) {
		vfree(hinfo);
		return -ENOMEM;
	}
	spin_lock_init(&hinfo->lock);

	switch (revision) {
	case 1:
		ops = &dl_seq_ops_v1;
		break;
	case 2:
		ops = &dl_seq_ops_v2;
		break;
	default:
		ops = &dl_seq_ops;
	}

	hinfo->pde = proc_create_seq_data(name, 0,
		(family == NFPROTO_IPV4) ?
		hashlimit_net->ipt_hashlimit : hashlimit_net->ip6t_hashlimit,
		ops, hinfo);
	if (hinfo->pde == NULL) {
		kfree(hinfo->name);
		vfree(hinfo);
		return -ENOMEM;
	}
	hinfo->net = net;

	INIT_DEFERRABLE_WORK(&hinfo->gc_work, htable_gc);
	queue_delayed_work(system_power_efficient_wq, &hinfo->gc_work,
			   msecs_to_jiffies(hinfo->cfg.gc_interval));

	hlist_add_head(&hinfo->node, &hashlimit_net->htables);

	return 0;
}