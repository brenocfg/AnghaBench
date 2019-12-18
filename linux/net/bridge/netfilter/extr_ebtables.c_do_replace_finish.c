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
struct net {int dummy; } ;
struct ebt_table_info {int nentries; int /*<<< orphan*/  entries_size; struct ebt_table_info* entries; int /*<<< orphan*/  counters; int /*<<< orphan*/ * chainstack; } ;
struct ebt_table {int (* check ) (struct ebt_table_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; struct ebt_table_info* private; int /*<<< orphan*/  me; } ;
struct ebt_replace {int num_counters; int /*<<< orphan*/  nentries; int /*<<< orphan*/  name; int /*<<< orphan*/  counters; int /*<<< orphan*/  valid_hooks; } ;
struct ebt_counter {int nentries; int /*<<< orphan*/  entries_size; struct ebt_counter* entries; int /*<<< orphan*/  counters; int /*<<< orphan*/ * chainstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BRIDGE ; 
 int /*<<< orphan*/  AUDIT_NETFILTER_CFG ; 
 int /*<<< orphan*/  EBT_ENTRY_ITERATE (struct ebt_table_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_context () ; 
 scalar_t__ audit_enabled ; 
 int /*<<< orphan*/  audit_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct ebt_table_info*,int) ; 
 int /*<<< orphan*/  ebt_cleanup_entry ; 
 int /*<<< orphan*/  ebt_free_table_info (struct ebt_table_info*) ; 
 int /*<<< orphan*/  ebt_mutex ; 
 int ebt_verify_pointers (struct ebt_replace*,struct ebt_table_info*) ; 
 struct ebt_table* find_table_lock (struct net*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_counters (int /*<<< orphan*/ ,struct ebt_table_info*,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*) ; 
 int stub1 (struct ebt_table_info*,int /*<<< orphan*/ ) ; 
 int translate_table (struct net*,int /*<<< orphan*/ ,struct ebt_table_info*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct ebt_table_info*) ; 
 struct ebt_table_info* vmalloc (unsigned long) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_replace_finish(struct net *net, struct ebt_replace *repl,
			      struct ebt_table_info *newinfo)
{
	int ret;
	struct ebt_counter *counterstmp = NULL;
	/* used to be able to unlock earlier */
	struct ebt_table_info *table;
	struct ebt_table *t;

	/* the user wants counters back
	 * the check on the size is done later, when we have the lock
	 */
	if (repl->num_counters) {
		unsigned long size = repl->num_counters * sizeof(*counterstmp);
		counterstmp = vmalloc(size);
		if (!counterstmp)
			return -ENOMEM;
	}

	newinfo->chainstack = NULL;
	ret = ebt_verify_pointers(repl, newinfo);
	if (ret != 0)
		goto free_counterstmp;

	ret = translate_table(net, repl->name, newinfo);

	if (ret != 0)
		goto free_counterstmp;

	t = find_table_lock(net, repl->name, &ret, &ebt_mutex);
	if (!t) {
		ret = -ENOENT;
		goto free_iterate;
	}

	/* the table doesn't like it */
	if (t->check && (ret = t->check(newinfo, repl->valid_hooks)))
		goto free_unlock;

	if (repl->num_counters && repl->num_counters != t->private->nentries) {
		ret = -EINVAL;
		goto free_unlock;
	}

	/* we have the mutex lock, so no danger in reading this pointer */
	table = t->private;
	/* make sure the table can only be rmmod'ed if it contains no rules */
	if (!table->nentries && newinfo->nentries && !try_module_get(t->me)) {
		ret = -ENOENT;
		goto free_unlock;
	} else if (table->nentries && !newinfo->nentries)
		module_put(t->me);
	/* we need an atomic snapshot of the counters */
	write_lock_bh(&t->lock);
	if (repl->num_counters)
		get_counters(t->private->counters, counterstmp,
		   t->private->nentries);

	t->private = newinfo;
	write_unlock_bh(&t->lock);
	mutex_unlock(&ebt_mutex);
	/* so, a user can change the chains while having messed up her counter
	 * allocation. Only reason why this is done is because this way the lock
	 * is held only once, while this doesn't bring the kernel into a
	 * dangerous state.
	 */
	if (repl->num_counters &&
	   copy_to_user(repl->counters, counterstmp,
	   repl->num_counters * sizeof(struct ebt_counter))) {
		/* Silent error, can't fail, new table is already in place */
		net_warn_ratelimited("ebtables: counters copy to user failed while replacing table\n");
	}

	/* decrease module count and free resources */
	EBT_ENTRY_ITERATE(table->entries, table->entries_size,
			  ebt_cleanup_entry, net, NULL);

	vfree(table->entries);
	ebt_free_table_info(table);
	vfree(table);
	vfree(counterstmp);

#ifdef CONFIG_AUDIT
	if (audit_enabled) {
		audit_log(audit_context(), GFP_KERNEL,
			  AUDIT_NETFILTER_CFG,
			  "table=%s family=%u entries=%u",
			  repl->name, AF_BRIDGE, repl->nentries);
	}
#endif
	return ret;

free_unlock:
	mutex_unlock(&ebt_mutex);
free_iterate:
	EBT_ENTRY_ITERATE(newinfo->entries, newinfo->entries_size,
			  ebt_cleanup_entry, net, NULL);
free_counterstmp:
	vfree(counterstmp);
	/* can be initialized in translate_table() */
	ebt_free_table_info(newinfo);
	return ret;
}