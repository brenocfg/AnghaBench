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
typedef  int u32 ;
struct nfs4_file {int fi_share_deny; int /*<<< orphan*/  fi_lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS4_SHARE_ACCESS_BOTH ; 
 int /*<<< orphan*/  __nfs4_file_get_access (struct nfs4_file*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_share_denied ; 

__attribute__((used)) static __be32
nfs4_file_get_access(struct nfs4_file *fp, u32 access)
{
	lockdep_assert_held(&fp->fi_lock);

	/* Does this access mode make sense? */
	if (access & ~NFS4_SHARE_ACCESS_BOTH)
		return nfserr_inval;

	/* Does it conflict with a deny mode already set? */
	if ((access & fp->fi_share_deny) != 0)
		return nfserr_share_denied;

	__nfs4_file_get_access(fp, access);
	return nfs_ok;
}