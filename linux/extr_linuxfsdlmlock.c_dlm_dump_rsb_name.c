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
typedef  int uint32_t ;
struct dlm_rsb {int dummy; } ;
struct dlm_ls {int ls_rsbtbl_size; TYPE_1__* ls_rsbtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  toss; int /*<<< orphan*/  keep; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_dump_rsb (struct dlm_rsb*) ; 
 int dlm_search_rsb_tree (int /*<<< orphan*/ *,char*,int,struct dlm_rsb**) ; 
 int jhash (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dlm_dump_rsb_name(struct dlm_ls *ls, char *name, int len)
{
	struct dlm_rsb *r = NULL;
	uint32_t hash, b;
	int error;

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	spin_lock(&ls->ls_rsbtbl[b].lock);
	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
	if (!error)
		goto out_dump;

	error = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	if (error)
		goto out;
 out_dump:
	dlm_dump_rsb(r);
 out:
	spin_unlock(&ls->ls_rsbtbl[b].lock);
}