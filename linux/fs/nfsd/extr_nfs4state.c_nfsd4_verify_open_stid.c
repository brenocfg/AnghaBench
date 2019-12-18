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
struct nfs4_stid {int sc_type; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  NFS4_CLOSED_DELEG_STID 130 
#define  NFS4_CLOSED_STID 129 
#define  NFS4_REVOKED_DELEG_STID 128 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_bad_stateid ; 
 int /*<<< orphan*/  nfserr_deleg_revoked ; 

__attribute__((used)) static __be32
nfsd4_verify_open_stid(struct nfs4_stid *s)
{
	__be32 ret = nfs_ok;

	switch (s->sc_type) {
	default:
		break;
	case 0:
	case NFS4_CLOSED_STID:
	case NFS4_CLOSED_DELEG_STID:
		ret = nfserr_bad_stateid;
		break;
	case NFS4_REVOKED_DELEG_STID:
		ret = nfserr_deleg_revoked;
	}
	return ret;
}