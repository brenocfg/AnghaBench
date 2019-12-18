#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sc_file; } ;
struct nfs4_delegation {TYPE_3__ dl_stid; } ;
struct file_lock {int /*<<< orphan*/  fl_file; int /*<<< orphan*/  fl_pid; scalar_t__ fl_owner; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_flags; int /*<<< orphan*/ * fl_lmops; } ;
typedef  scalar_t__ fl_owner_t ;
struct TYPE_8__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_6__ {TYPE_1__* fi_deleg_file; } ;
struct TYPE_5__ {int /*<<< orphan*/  nf_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_DELEG ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int NFS4_OPEN_DELEGATE_READ ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 TYPE_4__* current ; 
 struct file_lock* locks_alloc_lock () ; 
 int /*<<< orphan*/  nfsd_lease_mng_ops ; 

__attribute__((used)) static struct file_lock *nfs4_alloc_init_lease(struct nfs4_delegation *dp,
						int flag)
{
	struct file_lock *fl;

	fl = locks_alloc_lock();
	if (!fl)
		return NULL;
	fl->fl_lmops = &nfsd_lease_mng_ops;
	fl->fl_flags = FL_DELEG;
	fl->fl_type = flag == NFS4_OPEN_DELEGATE_READ? F_RDLCK: F_WRLCK;
	fl->fl_end = OFFSET_MAX;
	fl->fl_owner = (fl_owner_t)dp;
	fl->fl_pid = current->tgid;
	fl->fl_file = dp->dl_stid.sc_file->fi_deleg_file->nf_file;
	return fl;
}