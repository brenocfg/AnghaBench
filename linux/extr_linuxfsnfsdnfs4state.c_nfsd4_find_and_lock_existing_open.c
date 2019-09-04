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
struct nfsd4_open {int dummy; } ;
struct nfs4_ol_stateid {int /*<<< orphan*/  st_stid; } ;
struct nfs4_file {int /*<<< orphan*/  fi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_put_stid (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_ok ; 
 struct nfs4_ol_stateid* nfsd4_find_existing_open (struct nfs4_file*,struct nfsd4_open*) ; 
 scalar_t__ nfsd4_lock_ol_stateid (struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_ol_stateid *
nfsd4_find_and_lock_existing_open(struct nfs4_file *fp, struct nfsd4_open *open)
{
	struct nfs4_ol_stateid *stp;
	for (;;) {
		spin_lock(&fp->fi_lock);
		stp = nfsd4_find_existing_open(fp, open);
		spin_unlock(&fp->fi_lock);
		if (!stp || nfsd4_lock_ol_stateid(stp) == nfs_ok)
			break;
		nfs4_put_stid(&stp->st_stid);
	}
	return stp;
}