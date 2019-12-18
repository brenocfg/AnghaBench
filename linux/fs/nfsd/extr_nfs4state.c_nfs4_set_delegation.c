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
struct svc_fh {int dummy; } ;
struct nfsd_file {int /*<<< orphan*/  nf_file; } ;
struct nfs4_file {int fi_delegees; struct nfsd_file* fi_deleg_file; int /*<<< orphan*/  fi_lock; scalar_t__ fi_had_conflict; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_stid; int /*<<< orphan*/  dl_clnt_odstate; } ;
struct nfs4_clnt_odstate {int dummy; } ;
struct nfs4_client {int dummy; } ;
struct file_lock {int /*<<< orphan*/  fl_type; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADF ; 
 int ENOMEM ; 
 struct nfs4_delegation* ERR_PTR (int) ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  NFS4_OPEN_DELEGATE_READ ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct nfs4_delegation* alloc_init_deleg (struct nfs4_client*,struct nfs4_file*,struct svc_fh*,struct nfs4_clnt_odstate*) ; 
 struct nfsd_file* find_readable_file (struct nfs4_file*) ; 
 int hash_delegation_locked (struct nfs4_delegation*,struct nfs4_file*) ; 
 int /*<<< orphan*/  locks_free_lock (struct file_lock*) ; 
 struct file_lock* nfs4_alloc_init_lease (struct nfs4_delegation*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_delegation_exists (struct nfs4_client*,struct nfs4_file*) ; 
 int /*<<< orphan*/  nfs4_put_stid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 int /*<<< orphan*/  put_clnt_odstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_deleg_file (struct nfs4_file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_lock ; 
 int vfs_setlease (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file_lock**,void**) ; 

__attribute__((used)) static struct nfs4_delegation *
nfs4_set_delegation(struct nfs4_client *clp, struct svc_fh *fh,
		    struct nfs4_file *fp, struct nfs4_clnt_odstate *odstate)
{
	int status = 0;
	struct nfs4_delegation *dp;
	struct nfsd_file *nf;
	struct file_lock *fl;

	/*
	 * The fi_had_conflict and nfs_get_existing_delegation checks
	 * here are just optimizations; we'll need to recheck them at
	 * the end:
	 */
	if (fp->fi_had_conflict)
		return ERR_PTR(-EAGAIN);

	nf = find_readable_file(fp);
	if (!nf) {
		/* We should always have a readable file here */
		WARN_ON_ONCE(1);
		return ERR_PTR(-EBADF);
	}
	spin_lock(&state_lock);
	spin_lock(&fp->fi_lock);
	if (nfs4_delegation_exists(clp, fp))
		status = -EAGAIN;
	else if (!fp->fi_deleg_file) {
		fp->fi_deleg_file = nf;
		/* increment early to prevent fi_deleg_file from being
		 * cleared */
		fp->fi_delegees = 1;
		nf = NULL;
	} else
		fp->fi_delegees++;
	spin_unlock(&fp->fi_lock);
	spin_unlock(&state_lock);
	if (nf)
		nfsd_file_put(nf);
	if (status)
		return ERR_PTR(status);

	status = -ENOMEM;
	dp = alloc_init_deleg(clp, fp, fh, odstate);
	if (!dp)
		goto out_delegees;

	fl = nfs4_alloc_init_lease(dp, NFS4_OPEN_DELEGATE_READ);
	if (!fl)
		goto out_clnt_odstate;

	status = vfs_setlease(fp->fi_deleg_file->nf_file, fl->fl_type, &fl, NULL);
	if (fl)
		locks_free_lock(fl);
	if (status)
		goto out_clnt_odstate;

	spin_lock(&state_lock);
	spin_lock(&fp->fi_lock);
	if (fp->fi_had_conflict)
		status = -EAGAIN;
	else
		status = hash_delegation_locked(dp, fp);
	spin_unlock(&fp->fi_lock);
	spin_unlock(&state_lock);

	if (status)
		goto out_unlock;

	return dp;
out_unlock:
	vfs_setlease(fp->fi_deleg_file->nf_file, F_UNLCK, NULL, (void **)&dp);
out_clnt_odstate:
	put_clnt_odstate(dp->dl_clnt_odstate);
	nfs4_put_stid(&dp->dl_stid);
out_delegees:
	put_deleg_file(fp);
	return ERR_PTR(status);
}