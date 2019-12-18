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
struct svc_rqst {struct nfsd3_getaclargs* rq_argp; } ;
struct nfsd3_getaclargs {int /*<<< orphan*/  mask; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * nfs3svc_decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs3svc_decode_getaclargs(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_getaclargs *args = rqstp->rq_argp;

	p = nfs3svc_decode_fh(p, &args->fh);
	if (!p)
		return 0;
	args->mask = ntohl(*p); p++;

	return xdr_argsize_check(rqstp, p);
}