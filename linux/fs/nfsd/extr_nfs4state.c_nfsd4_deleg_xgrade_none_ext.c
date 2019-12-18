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
struct nfsd4_open {scalar_t__ op_deleg_want; int /*<<< orphan*/  op_why_no_deleg; void* op_delegate_type; } ;
struct nfs4_delegation {scalar_t__ dl_type; } ;

/* Variables and functions */
 void* NFS4_OPEN_DELEGATE_NONE_EXT ; 
 scalar_t__ NFS4_OPEN_DELEGATE_WRITE ; 
 scalar_t__ NFS4_SHARE_WANT_READ_DELEG ; 
 scalar_t__ NFS4_SHARE_WANT_WRITE_DELEG ; 
 int /*<<< orphan*/  WND4_NOT_SUPP_DOWNGRADE ; 
 int /*<<< orphan*/  WND4_NOT_SUPP_UPGRADE ; 

__attribute__((used)) static void nfsd4_deleg_xgrade_none_ext(struct nfsd4_open *open,
					struct nfs4_delegation *dp)
{
	if (open->op_deleg_want == NFS4_SHARE_WANT_READ_DELEG &&
	    dp->dl_type == NFS4_OPEN_DELEGATE_WRITE) {
		open->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
		open->op_why_no_deleg = WND4_NOT_SUPP_DOWNGRADE;
	} else if (open->op_deleg_want == NFS4_SHARE_WANT_WRITE_DELEG &&
		   dp->dl_type == NFS4_OPEN_DELEGATE_WRITE) {
		open->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
		open->op_why_no_deleg = WND4_NOT_SUPP_UPGRADE;
	}
	/* Otherwise the client must be confused wanting a delegation
	 * it already has, therefore we don't return
	 * NFS4_OPEN_DELEGATE_NONE_EXT and reason.
	 */
}