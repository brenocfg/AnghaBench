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
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct svc_rqst {struct nfsd3_sattrargs* rq_argp; } ;
struct nfsd3_sattrargs {int /*<<< orphan*/  guardtime; int /*<<< orphan*/  check_guard; int /*<<< orphan*/  attrs; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decode_sattr3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * decode_time3 (int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  nfsd_user_namespace (struct svc_rqst*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfs3svc_decode_sattrargs(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_sattrargs *args = rqstp->rq_argp;

	p = decode_fh(p, &args->fh);
	if (!p)
		return 0;
	p = decode_sattr3(p, &args->attrs, nfsd_user_namespace(rqstp));

	if ((args->check_guard = ntohl(*p++)) != 0) { 
		struct timespec time; 
		p = decode_time3(p, &time);
		args->guardtime = time.tv_sec;
	}

	return xdr_argsize_check(rqstp, p);
}