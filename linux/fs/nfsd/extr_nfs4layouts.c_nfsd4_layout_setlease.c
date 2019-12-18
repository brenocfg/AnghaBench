#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfs4_layout_stateid {size_t ls_layout_type; TYPE_1__* ls_file; } ;
struct file_lock {int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_file; int /*<<< orphan*/  fl_pid; struct nfs4_layout_stateid* fl_owner; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_flags; int /*<<< orphan*/ * fl_lmops; } ;
struct TYPE_6__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_5__ {scalar_t__ disable_recalls; } ;
struct TYPE_4__ {int /*<<< orphan*/  nf_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FL_LAYOUT ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 TYPE_3__* current ; 
 struct file_lock* locks_alloc_lock () ; 
 int /*<<< orphan*/  locks_free_lock (struct file_lock*) ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 TYPE_2__** nfsd4_layout_ops ; 
 int /*<<< orphan*/  nfsd4_layouts_lm_ops ; 
 int vfs_setlease (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file_lock**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsd4_layout_setlease(struct nfs4_layout_stateid *ls)
{
	struct file_lock *fl;
	int status;

	if (nfsd4_layout_ops[ls->ls_layout_type]->disable_recalls)
		return 0;

	fl = locks_alloc_lock();
	if (!fl)
		return -ENOMEM;
	locks_init_lock(fl);
	fl->fl_lmops = &nfsd4_layouts_lm_ops;
	fl->fl_flags = FL_LAYOUT;
	fl->fl_type = F_RDLCK;
	fl->fl_end = OFFSET_MAX;
	fl->fl_owner = ls;
	fl->fl_pid = current->tgid;
	fl->fl_file = ls->ls_file->nf_file;

	status = vfs_setlease(fl->fl_file, fl->fl_type, &fl, NULL);
	if (status) {
		locks_free_lock(fl);
		return status;
	}
	BUG_ON(fl != NULL);
	return 0;
}