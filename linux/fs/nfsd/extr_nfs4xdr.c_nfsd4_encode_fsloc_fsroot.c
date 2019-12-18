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
struct svc_export {int /*<<< orphan*/  ex_path; } ;
struct path {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  PTR_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 int /*<<< orphan*/  nfsd4_encode_path (struct xdr_stream*,int /*<<< orphan*/ *,struct path const*) ; 
 int /*<<< orphan*/  nfserrno (int /*<<< orphan*/ ) ; 
 struct svc_export* rqst_find_fsidzero_export (struct svc_rqst*) ; 

__attribute__((used)) static __be32 nfsd4_encode_fsloc_fsroot(struct xdr_stream *xdr,
			struct svc_rqst *rqstp, const struct path *path)
{
	struct svc_export *exp_ps;
	__be32 res;

	exp_ps = rqst_find_fsidzero_export(rqstp);
	if (IS_ERR(exp_ps))
		return nfserrno(PTR_ERR(exp_ps));
	res = nfsd4_encode_path(xdr, &exp_ps->ex_path, path);
	exp_put(exp_ps);
	return res;
}