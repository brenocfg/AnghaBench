#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nlm_lock {char* caller; TYPE_7__ fl; scalar_t__ svid; TYPE_3__ oh; int /*<<< orphan*/  fh; } ;
struct nlm_args {int /*<<< orphan*/  cookie; struct nlm_lock lock; } ;
struct nlm_rqst {int /*<<< orphan*/  a_owner; TYPE_2__* a_host; struct nlm_args a_args; } ;
struct nfs_fh {int dummy; } ;
struct TYPE_12__ {TYPE_4__* owner; } ;
struct TYPE_13__ {TYPE_5__ nfs_fl; } ;
struct file_lock {int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; TYPE_6__ fl_u; int /*<<< orphan*/  fl_file; } ;
struct TYPE_11__ {scalar_t__ pid; } ;
struct TYPE_9__ {TYPE_1__* h_rpcclnt; } ;
struct TYPE_8__ {char* cl_nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmclnt_next_cookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int,char*) ; 

__attribute__((used)) static void nlmclnt_setlockargs(struct nlm_rqst *req, struct file_lock *fl)
{
	struct nlm_args	*argp = &req->a_args;
	struct nlm_lock	*lock = &argp->lock;
	char *nodename = req->a_host->h_rpcclnt->cl_nodename;

	nlmclnt_next_cookie(&argp->cookie);
	memcpy(&lock->fh, NFS_FH(locks_inode(fl->fl_file)), sizeof(struct nfs_fh));
	lock->caller  = nodename;
	lock->oh.data = req->a_owner;
	lock->oh.len  = snprintf(req->a_owner, sizeof(req->a_owner), "%u@%s",
				(unsigned int)fl->fl_u.nfs_fl.owner->pid,
				nodename);
	lock->svid = fl->fl_u.nfs_fl.owner->pid;
	lock->fl.fl_start = fl->fl_start;
	lock->fl.fl_end = fl->fl_end;
	lock->fl.fl_type = fl->fl_type;
}