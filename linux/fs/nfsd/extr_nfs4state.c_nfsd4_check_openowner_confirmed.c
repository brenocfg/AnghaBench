#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs4_ol_stateid {TYPE_2__* st_stateowner; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ so_is_open_owner; } ;
struct TYPE_3__ {int oo_flags; } ;

/* Variables and functions */
 int NFS4_OO_CONFIRMED ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_bad_stateid ; 
 TYPE_1__* openowner (TYPE_2__*) ; 

__attribute__((used)) static __be32 nfsd4_check_openowner_confirmed(struct nfs4_ol_stateid *ols)
{
	if (ols->st_stateowner->so_is_open_owner &&
	    !(openowner(ols->st_stateowner)->oo_flags & NFS4_OO_CONFIRMED))
		return nfserr_bad_stateid;
	return nfs_ok;
}