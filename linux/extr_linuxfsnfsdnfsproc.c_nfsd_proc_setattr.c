#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct svc_rqst {struct nfsd_attrstat* rq_resp; struct nfsd_sattrargs* rq_argp; } ;
struct svc_fh {int /*<<< orphan*/  fh_dentry; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;
struct iattr {int ia_valid; TYPE_2__ ia_atime; TYPE_1__ ia_mtime; scalar_t__ ia_size; } ;
struct nfsd_sattrargs {int /*<<< orphan*/  fh; struct iattr attrs; } ;
struct nfsd_attrstat {int /*<<< orphan*/  fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ATTR_ATIME_SET ; 
 int ATTR_MTIME_SET ; 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,long) ; 
 struct svc_fh* fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_seconds () ; 
 scalar_t__ nfsd_return_attrs (scalar_t__,struct nfsd_attrstat*) ; 
 scalar_t__ nfsd_setattr (struct svc_rqst*,struct svc_fh*,struct iattr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setattr_prepare (int /*<<< orphan*/ ,struct iattr*) ; 

__attribute__((used)) static __be32
nfsd_proc_setattr(struct svc_rqst *rqstp)
{
	struct nfsd_sattrargs *argp = rqstp->rq_argp;
	struct nfsd_attrstat *resp = rqstp->rq_resp;
	struct iattr *iap = &argp->attrs;
	struct svc_fh *fhp;
	__be32 nfserr;

	dprintk("nfsd: SETATTR  %s, valid=%x, size=%ld\n",
		SVCFH_fmt(&argp->fh),
		argp->attrs.ia_valid, (long) argp->attrs.ia_size);

	fhp = fh_copy(&resp->fh, &argp->fh);

	/*
	 * NFSv2 does not differentiate between "set-[ac]time-to-now"
	 * which only requires access, and "set-[ac]time-to-X" which
	 * requires ownership.
	 * So if it looks like it might be "set both to the same time which
	 * is close to now", and if setattr_prepare fails, then we
	 * convert to "set to now" instead of "set to explicit time"
	 *
	 * We only call setattr_prepare as the last test as technically
	 * it is not an interface that we should be using.
	 */
#define BOTH_TIME_SET (ATTR_ATIME_SET | ATTR_MTIME_SET)
#define	MAX_TOUCH_TIME_ERROR (30*60)
	if ((iap->ia_valid & BOTH_TIME_SET) == BOTH_TIME_SET &&
	    iap->ia_mtime.tv_sec == iap->ia_atime.tv_sec) {
		/*
		 * Looks probable.
		 *
		 * Now just make sure time is in the right ballpark.
		 * Solaris, at least, doesn't seem to care what the time
		 * request is.  We require it be within 30 minutes of now.
		 */
		time_t delta = iap->ia_atime.tv_sec - get_seconds();

		nfserr = fh_verify(rqstp, fhp, 0, NFSD_MAY_NOP);
		if (nfserr)
			goto done;

		if (delta < 0)
			delta = -delta;
		if (delta < MAX_TOUCH_TIME_ERROR &&
		    setattr_prepare(fhp->fh_dentry, iap) != 0) {
			/*
			 * Turn off ATTR_[AM]TIME_SET but leave ATTR_[AM]TIME.
			 * This will cause notify_change to set these times
			 * to "now"
			 */
			iap->ia_valid &= ~BOTH_TIME_SET;
		}
	}

	nfserr = nfsd_setattr(rqstp, fhp, iap, 0, (time_t)0);
done:
	return nfsd_return_attrs(nfserr, resp);
}