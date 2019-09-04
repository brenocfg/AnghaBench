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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int /*<<< orphan*/ * p; } ;
struct xdr_buf {int dummy; } ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct svc_export {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_encode_fattr (struct xdr_stream*,struct svc_fh*,struct svc_export*,struct dentry*,int /*<<< orphan*/ *,struct svc_rqst*,int) ; 
 int /*<<< orphan*/  svcxdr_init_encode_from_buffer (struct xdr_stream*,struct xdr_buf*,int /*<<< orphan*/ *,int) ; 

__be32 nfsd4_encode_fattr_to_buf(__be32 **p, int words,
			struct svc_fh *fhp, struct svc_export *exp,
			struct dentry *dentry, u32 *bmval,
			struct svc_rqst *rqstp, int ignore_crossmnt)
{
	struct xdr_buf dummy;
	struct xdr_stream xdr;
	__be32 ret;

	svcxdr_init_encode_from_buffer(&xdr, &dummy, *p, words << 2);
	ret = nfsd4_encode_fattr(&xdr, fhp, exp, dentry, bmval, rqstp,
							ignore_crossmnt);
	*p = xdr.p;
	return ret;
}