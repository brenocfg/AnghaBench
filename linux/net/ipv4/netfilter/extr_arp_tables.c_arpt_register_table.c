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
struct xt_table_info {void* entries; int /*<<< orphan*/  member_0; } ;
struct xt_table {int /*<<< orphan*/  valid_hooks; } ;
struct nf_hook_ops {int dummy; } ;
struct net {int dummy; } ;
struct arpt_replace {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct xt_table*) ; 
 int PTR_ERR (struct xt_table*) ; 
 int /*<<< orphan*/  WRITE_ONCE (struct xt_table*,struct xt_table*) ; 
 int /*<<< orphan*/  __arpt_unregister_table (struct xt_table*) ; 
 int /*<<< orphan*/  hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nf_register_net_hooks (struct net*,struct nf_hook_ops const*,int /*<<< orphan*/ ) ; 
 int translate_table (struct xt_table_info*,void*,struct arpt_replace const*) ; 
 struct xt_table_info* xt_alloc_table_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_free_table_info (struct xt_table_info*) ; 
 struct xt_table* xt_register_table (struct net*,struct xt_table const*,struct xt_table_info*,struct xt_table_info*) ; 

int arpt_register_table(struct net *net,
			const struct xt_table *table,
			const struct arpt_replace *repl,
			const struct nf_hook_ops *ops,
			struct xt_table **res)
{
	int ret;
	struct xt_table_info *newinfo;
	struct xt_table_info bootstrap = {0};
	void *loc_cpu_entry;
	struct xt_table *new_table;

	newinfo = xt_alloc_table_info(repl->size);
	if (!newinfo)
		return -ENOMEM;

	loc_cpu_entry = newinfo->entries;
	memcpy(loc_cpu_entry, repl->entries, repl->size);

	ret = translate_table(newinfo, loc_cpu_entry, repl);
	if (ret != 0)
		goto out_free;

	new_table = xt_register_table(net, table, &bootstrap, newinfo);
	if (IS_ERR(new_table)) {
		ret = PTR_ERR(new_table);
		goto out_free;
	}

	/* set res now, will see skbs right after nf_register_net_hooks */
	WRITE_ONCE(*res, new_table);

	ret = nf_register_net_hooks(net, ops, hweight32(table->valid_hooks));
	if (ret != 0) {
		__arpt_unregister_table(new_table);
		*res = NULL;
	}

	return ret;

out_free:
	xt_free_table_info(newinfo);
	return ret;
}