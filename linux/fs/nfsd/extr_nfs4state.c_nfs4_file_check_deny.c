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
struct nfs4_file {int /*<<< orphan*/ * fi_access; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS4_SHARE_DENY_BOTH ; 
 int NFS4_SHARE_DENY_READ ; 
 int NFS4_SHARE_DENY_WRITE ; 
 size_t O_RDONLY ; 
 size_t O_WRONLY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_share_denied ; 

__attribute__((used)) static __be32 nfs4_file_check_deny(struct nfs4_file *fp, u32 deny)
{
	/* Common case is that there is no deny mode. */
	if (deny) {
		/* Does this deny mode make sense? */
		if (deny & ~NFS4_SHARE_DENY_BOTH)
			return nfserr_inval;

		if ((deny & NFS4_SHARE_DENY_READ) &&
		    atomic_read(&fp->fi_access[O_RDONLY]))
			return nfserr_share_denied;

		if ((deny & NFS4_SHARE_DENY_WRITE) &&
		    atomic_read(&fp->fi_access[O_WRONLY]))
			return nfserr_share_denied;
	}
	return nfs_ok;
}