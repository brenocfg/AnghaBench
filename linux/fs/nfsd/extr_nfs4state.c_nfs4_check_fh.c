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
struct svc_fh {int /*<<< orphan*/  fh_handle; } ;
struct nfs4_stid {TYPE_1__* sc_file; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  fi_fhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  fh_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_bad_stateid ; 

__attribute__((used)) static inline __be32 nfs4_check_fh(struct svc_fh *fhp, struct nfs4_stid *stp)
{
	if (!fh_match(&fhp->fh_handle, &stp->sc_file->fi_fhandle))
		return nfserr_bad_stateid;
	return nfs_ok;
}