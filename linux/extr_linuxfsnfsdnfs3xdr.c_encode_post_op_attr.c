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
struct svc_rqst {int dummy; } ;
struct svc_fh {struct dentry* fh_dentry; } ;
struct kstat {int /*<<< orphan*/  mtime; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/ * encode_fattr3 (struct svc_rqst*,int /*<<< orphan*/ *,struct svc_fh*,struct kstat*) ; 
 int /*<<< orphan*/  fh_getattr (struct svc_fh*,struct kstat*) ; 
 int /*<<< orphan*/  lease_get_mtime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_one ; 
 int /*<<< orphan*/  xdr_zero ; 

__attribute__((used)) static __be32 *
encode_post_op_attr(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp)
{
	struct dentry *dentry = fhp->fh_dentry;
	if (dentry && d_really_is_positive(dentry)) {
	        __be32 err;
		struct kstat stat;

		err = fh_getattr(fhp, &stat);
		if (!err) {
			*p++ = xdr_one;		/* attributes follow */
			lease_get_mtime(d_inode(dentry), &stat.mtime);
			return encode_fattr3(rqstp, p, fhp, &stat);
		}
	}
	*p++ = xdr_zero;
	return p;
}