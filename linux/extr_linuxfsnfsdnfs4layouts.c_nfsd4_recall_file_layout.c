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
struct TYPE_3__ {int /*<<< orphan*/  sc_count; int /*<<< orphan*/  sc_stateid; TYPE_2__* sc_file; } ;
struct nfs4_layout_stateid {int ls_recalled; int /*<<< orphan*/  ls_lock; int /*<<< orphan*/  ls_recall; TYPE_1__ ls_stid; int /*<<< orphan*/  ls_layouts; } ;
struct TYPE_4__ {int /*<<< orphan*/  fi_lo_recalls; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_run_cb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfsd_layout_recall (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsd4_recall_file_layout(struct nfs4_layout_stateid *ls)
{
	spin_lock(&ls->ls_lock);
	if (ls->ls_recalled)
		goto out_unlock;

	ls->ls_recalled = true;
	atomic_inc(&ls->ls_stid.sc_file->fi_lo_recalls);
	if (list_empty(&ls->ls_layouts))
		goto out_unlock;

	trace_nfsd_layout_recall(&ls->ls_stid.sc_stateid);

	refcount_inc(&ls->ls_stid.sc_count);
	nfsd4_run_cb(&ls->ls_recall);

out_unlock:
	spin_unlock(&ls->ls_lock);
}