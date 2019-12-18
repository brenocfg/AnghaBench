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
struct nfsd_net {int in_grace; int /*<<< orphan*/  rec_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  mnt_drop_write_file (int /*<<< orphan*/ ) ; 
 int mnt_want_write_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_release_reclaim (struct nfsd_net*) ; 
 int nfsd4_list_rec_dir (int /*<<< orphan*/ ,struct nfsd_net*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_old ; 
 int /*<<< orphan*/  vfs_fsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsd4_recdir_purge_old(struct nfsd_net *nn)
{
	int status;

	nn->in_grace = false;
	if (!nn->rec_file)
		return;
	status = mnt_want_write_file(nn->rec_file);
	if (status)
		goto out;
	status = nfsd4_list_rec_dir(purge_old, nn);
	if (status == 0)
		vfs_fsync(nn->rec_file, 0);
	mnt_drop_write_file(nn->rec_file);
out:
	nfs4_release_reclaim(nn);
	if (status)
		printk("nfsd4: failed to purge old clients from recovery"
			" directory %pD\n", nn->rec_file);
}