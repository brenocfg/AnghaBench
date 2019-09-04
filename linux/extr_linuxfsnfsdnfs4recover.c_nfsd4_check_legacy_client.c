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
struct nfsd_net {int dummy; } ;
struct nfs4_client_reclaim {struct nfs4_client* cr_clp; } ;
struct nfs4_client {int /*<<< orphan*/  cl_flags; int /*<<< orphan*/  cl_name; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int ENOENT ; 
 int HEXDIR_LEN ; 
 int /*<<< orphan*/  NFSD4_CLIENT_STABLE ; 
 int /*<<< orphan*/  legacy_recdir_name_error (struct nfs4_client*,int) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs4_make_rec_clidname (char*,int /*<<< orphan*/ *) ; 
 struct nfs4_client_reclaim* nfsd4_find_reclaim_client (char*,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsd4_check_legacy_client(struct nfs4_client *clp)
{
	int status;
	char dname[HEXDIR_LEN];
	struct nfs4_client_reclaim *crp;
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	/* did we already find that this client is stable? */
	if (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		return 0;

	status = nfs4_make_rec_clidname(dname, &clp->cl_name);
	if (status) {
		legacy_recdir_name_error(clp, status);
		return status;
	}

	/* look for it in the reclaim hashtable otherwise */
	crp = nfsd4_find_reclaim_client(dname, nn);
	if (crp) {
		set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
		crp->cr_clp = clp;
		return 0;
	}

	return -ENOENT;
}