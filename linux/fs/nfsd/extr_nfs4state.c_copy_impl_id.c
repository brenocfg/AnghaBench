#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct nfsd4_exchange_id {TYPE_2__ nii_time; TYPE_4__ nii_name; TYPE_4__ nii_domain; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct nfs4_client {TYPE_1__ cl_nii_time; TYPE_3__ cl_nii_name; TYPE_3__ cl_nii_domain; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  nfserr_jukebox ; 
 int /*<<< orphan*/  xdr_netobj_dup (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 copy_impl_id(struct nfs4_client *clp,
				struct nfsd4_exchange_id *exid)
{
	if (!exid->nii_domain.data)
		return 0;
	xdr_netobj_dup(&clp->cl_nii_domain, &exid->nii_domain, GFP_KERNEL);
	if (!clp->cl_nii_domain.data)
		return nfserr_jukebox;
	xdr_netobj_dup(&clp->cl_nii_name, &exid->nii_name, GFP_KERNEL);
	if (!clp->cl_nii_name.data)
		return nfserr_jukebox;
	clp->cl_nii_time.tv_sec = exid->nii_time.tv_sec;
	clp->cl_nii_time.tv_nsec = exid->nii_time.tv_nsec;
	return 0;
}