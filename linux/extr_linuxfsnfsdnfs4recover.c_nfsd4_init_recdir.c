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
struct nfsd_net {int in_grace; int /*<<< orphan*/ * rec_file; } ;
struct net {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filp_open (int,int,int /*<<< orphan*/ ) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_reset_creds (struct cred const*) ; 
 int nfs4_save_creds (struct cred const**) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int user_recovery_dirname ; 

__attribute__((used)) static int
nfsd4_init_recdir(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	const struct cred *original_cred;
	int status;

	printk("NFSD: Using %s as the NFSv4 state recovery directory\n",
			user_recovery_dirname);

	BUG_ON(nn->rec_file);

	status = nfs4_save_creds(&original_cred);
	if (status < 0) {
		printk("NFSD: Unable to change credentials to find recovery"
		       " directory: error %d\n",
		       status);
		return status;
	}

	nn->rec_file = filp_open(user_recovery_dirname, O_RDONLY | O_DIRECTORY, 0);
	if (IS_ERR(nn->rec_file)) {
		printk("NFSD: unable to find recovery directory %s\n",
				user_recovery_dirname);
		status = PTR_ERR(nn->rec_file);
		nn->rec_file = NULL;
	}

	nfs4_reset_creds(original_cred);
	if (!status)
		nn->in_grace = true;
	return status;
}