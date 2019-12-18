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
struct xdr_stream {int dummy; } ;
struct svc_rqst {int dummy; } ;
struct nfsd4_fs_locations {int locations_count; int /*<<< orphan*/ * locations; } ;
struct svc_export {int /*<<< orphan*/  ex_path; struct nfsd4_fs_locations ex_fslocs; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ nfsd4_encode_fs_location4 (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd4_encode_fsloc_fsroot (struct xdr_stream*,struct svc_rqst*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfserr_resource ; 
 scalar_t__* xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 nfsd4_encode_fs_locations(struct xdr_stream *xdr,
			struct svc_rqst *rqstp, struct svc_export *exp)
{
	__be32 status;
	int i;
	__be32 *p;
	struct nfsd4_fs_locations *fslocs = &exp->ex_fslocs;

	status = nfsd4_encode_fsloc_fsroot(xdr, rqstp, &exp->ex_path);
	if (status)
		return status;
	p = xdr_reserve_space(xdr, 4);
	if (!p)
		return nfserr_resource;
	*p++ = cpu_to_be32(fslocs->locations_count);
	for (i=0; i<fslocs->locations_count; i++) {
		status = nfsd4_encode_fs_location4(xdr, &fslocs->locations[i]);
		if (status)
			return status;
	}
	return 0;
}