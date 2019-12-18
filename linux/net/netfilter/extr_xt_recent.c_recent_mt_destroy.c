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
struct xt_recent_mtinfo_v1 {int /*<<< orphan*/  name; } ;
struct xt_mtdtor_param {struct xt_recent_mtinfo_v1* matchinfo; int /*<<< orphan*/  net; } ;
struct recent_table {scalar_t__ refcnt; int /*<<< orphan*/  name; int /*<<< orphan*/  list; } ;
struct recent_net {int /*<<< orphan*/ * xt_recent; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recent_lock ; 
 int /*<<< orphan*/  recent_mutex ; 
 struct recent_net* recent_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recent_table_flush (struct recent_table*) ; 
 int /*<<< orphan*/  recent_table_free (struct recent_table*) ; 
 struct recent_table* recent_table_lookup (struct recent_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recent_mt_destroy(const struct xt_mtdtor_param *par)
{
	struct recent_net *recent_net = recent_pernet(par->net);
	const struct xt_recent_mtinfo_v1 *info = par->matchinfo;
	struct recent_table *t;

	mutex_lock(&recent_mutex);
	t = recent_table_lookup(recent_net, info->name);
	if (--t->refcnt == 0) {
		spin_lock_bh(&recent_lock);
		list_del(&t->list);
		spin_unlock_bh(&recent_lock);
#ifdef CONFIG_PROC_FS
		if (recent_net->xt_recent != NULL)
			remove_proc_entry(t->name, recent_net->xt_recent);
#endif
		recent_table_flush(t);
		recent_table_free(t);
	}
	mutex_unlock(&recent_mutex);
}