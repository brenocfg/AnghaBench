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
struct nfsd_net {int dummy; } ;
struct nfsd4_compound_state {TYPE_1__* clp; } ;
typedef  int /*<<< orphan*/  clientid_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  cl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD4_CLIENT_RECLAIM_COMPLETE ; 
 scalar_t__ lookup_clientid (int /*<<< orphan*/ *,struct nfsd4_compound_state*,struct nfsd_net*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_client_record_check (TYPE_1__*) ; 
 scalar_t__ nfserr_no_grace ; 
 scalar_t__ nfserr_reclaim_bad ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__be32
nfs4_check_open_reclaim(clientid_t *clid,
		struct nfsd4_compound_state *cstate,
		struct nfsd_net *nn)
{
	__be32 status;

	/* find clientid in conf_id_hashtbl */
	status = lookup_clientid(clid, cstate, nn);
	if (status)
		return nfserr_reclaim_bad;

	if (test_bit(NFSD4_CLIENT_RECLAIM_COMPLETE, &cstate->clp->cl_flags))
		return nfserr_no_grace;

	if (nfsd4_client_record_check(cstate->clp))
		return nfserr_reclaim_bad;

	return nfs_ok;
}