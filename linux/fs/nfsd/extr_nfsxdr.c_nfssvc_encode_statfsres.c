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
struct svc_rqst {struct nfsd_statfsres* rq_resp; } ;
struct kstatfs {int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; } ;
struct nfsd_statfsres {struct kstatfs stats; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFSSVC_MAXBLKSIZE_V2 ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfssvc_encode_statfsres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd_statfsres *resp = rqstp->rq_resp;
	struct kstatfs	*stat = &resp->stats;

	*p++ = htonl(NFSSVC_MAXBLKSIZE_V2);	/* max transfer size */
	*p++ = htonl(stat->f_bsize);
	*p++ = htonl(stat->f_blocks);
	*p++ = htonl(stat->f_bfree);
	*p++ = htonl(stat->f_bavail);
	return xdr_ressize_check(rqstp, p);
}