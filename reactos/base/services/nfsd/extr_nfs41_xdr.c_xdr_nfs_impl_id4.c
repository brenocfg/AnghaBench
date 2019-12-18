#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* nii_domain; unsigned char* nii_name; int /*<<< orphan*/  nii_date; int /*<<< orphan*/  nii_name_len; int /*<<< orphan*/  nii_domain_len; } ;
typedef  TYPE_1__ nfs_impl_id4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_nfstime4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t xdr_nfs_impl_id4(
    XDR *xdr,
    nfs_impl_id4 *nii)
{
    unsigned char *nii_domain = nii->nii_domain;
    unsigned char *nii_name = nii->nii_name;

    if (!xdr_bytes(xdr, (char **)&nii_domain, &nii->nii_domain_len, NFS4_OPAQUE_LIMIT))
        return FALSE;

    if (!xdr_bytes(xdr, (char **)&nii_name, &nii->nii_name_len, NFS4_OPAQUE_LIMIT))
        return FALSE;

    return xdr_nfstime4(xdr, &nii->nii_date);
}