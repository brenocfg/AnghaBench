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
typedef  int /*<<< orphan*/  u64 ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_pre_ctime; int /*<<< orphan*/  fh_pre_mtime; scalar_t__ fh_pre_size; scalar_t__ fh_pre_saved; scalar_t__ fh_post_saved; struct dentry* fh_dentry; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/ * encode_post_op_attr (struct svc_rqst*,int /*<<< orphan*/ *,struct svc_fh*) ; 
 int /*<<< orphan*/ * encode_saved_post_attr (struct svc_rqst*,int /*<<< orphan*/ *,struct svc_fh*) ; 
 int /*<<< orphan*/ * encode_time3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_one ; 
 void* xdr_zero ; 

__attribute__((used)) static __be32 *
encode_wcc_data(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp)
{
	struct dentry	*dentry = fhp->fh_dentry;

	if (dentry && d_really_is_positive(dentry) && fhp->fh_post_saved) {
		if (fhp->fh_pre_saved) {
			*p++ = xdr_one;
			p = xdr_encode_hyper(p, (u64) fhp->fh_pre_size);
			p = encode_time3(p, &fhp->fh_pre_mtime);
			p = encode_time3(p, &fhp->fh_pre_ctime);
		} else {
			*p++ = xdr_zero;
		}
		return encode_saved_post_attr(rqstp, p, fhp);
	}
	/* no pre- or post-attrs */
	*p++ = xdr_zero;
	return encode_post_op_attr(rqstp, p, fhp);
}