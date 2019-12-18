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
struct dlm_recover {int nodes_count; struct dlm_recover* nodes; scalar_t__ seq; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recoverd_task; int /*<<< orphan*/  ls_flags; int /*<<< orphan*/  ls_recover_lock; struct dlm_recover* ls_recover_args; scalar_t__ ls_recover_seq; int /*<<< orphan*/  ls_name; } ;
struct dlm_config_node {int nodes_count; struct dlm_config_node* nodes; scalar_t__ seq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  LSFL_RECOVER_WORK ; 
 int dlm_config_nodes (int /*<<< orphan*/ ,struct dlm_recover**,int*) ; 
 int /*<<< orphan*/  dlm_locking_stopped (struct dlm_ls*) ; 
 int /*<<< orphan*/  kfree (struct dlm_recover*) ; 
 struct dlm_recover* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

int dlm_ls_start(struct dlm_ls *ls)
{
	struct dlm_recover *rv, *rv_old;
	struct dlm_config_node *nodes = NULL;
	int error, count;

	rv = kzalloc(sizeof(*rv), GFP_NOFS);
	if (!rv)
		return -ENOMEM;

	error = dlm_config_nodes(ls->ls_name, &nodes, &count);
	if (error < 0)
		goto fail_rv;

	spin_lock(&ls->ls_recover_lock);

	/* the lockspace needs to be stopped before it can be started */

	if (!dlm_locking_stopped(ls)) {
		spin_unlock(&ls->ls_recover_lock);
		log_error(ls, "start ignored: lockspace running");
		error = -EINVAL;
		goto fail;
	}

	rv->nodes = nodes;
	rv->nodes_count = count;
	rv->seq = ++ls->ls_recover_seq;
	rv_old = ls->ls_recover_args;
	ls->ls_recover_args = rv;
	spin_unlock(&ls->ls_recover_lock);

	if (rv_old) {
		log_error(ls, "unused recovery %llx %d",
			  (unsigned long long)rv_old->seq, rv_old->nodes_count);
		kfree(rv_old->nodes);
		kfree(rv_old);
	}

	set_bit(LSFL_RECOVER_WORK, &ls->ls_flags);
	wake_up_process(ls->ls_recoverd_task);
	return 0;

 fail:
	kfree(nodes);
 fail_rv:
	kfree(rv);
	return error;
}