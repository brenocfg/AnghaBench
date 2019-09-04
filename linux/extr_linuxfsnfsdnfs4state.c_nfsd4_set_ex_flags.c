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
struct nfsd4_exchange_id {int /*<<< orphan*/  flags; } ;
struct nfs4_client {int /*<<< orphan*/  cl_exchange_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXCHGID4_FLAG_SUPP_MOVED_REFER ; 
 int /*<<< orphan*/  EXCHGID4_FLAG_USE_NON_PNFS ; 

__attribute__((used)) static void
nfsd4_set_ex_flags(struct nfs4_client *new, struct nfsd4_exchange_id *clid)
{
#ifdef CONFIG_NFSD_PNFS
	new->cl_exchange_flags |= EXCHGID4_FLAG_USE_PNFS_MDS;
#else
	new->cl_exchange_flags |= EXCHGID4_FLAG_USE_NON_PNFS;
#endif

	/* Referrals are supported, Migration is not. */
	new->cl_exchange_flags |= EXCHGID4_FLAG_SUPP_MOVED_REFER;

	/* set the wire flags to return to client. */
	clid->flags = new->cl_exchange_flags;
}