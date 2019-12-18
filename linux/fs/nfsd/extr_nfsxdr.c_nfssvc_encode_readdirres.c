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
struct TYPE_4__ {unsigned long page_len; } ;
struct svc_rqst {TYPE_2__ rq_res; struct nfsd_readdirres* rq_resp; } ;
struct TYPE_3__ {scalar_t__ err; } ;
struct nfsd_readdirres {TYPE_1__ common; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ nfserr_eof ; 
 int /*<<< orphan*/  xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfssvc_encode_readdirres(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd_readdirres *resp = rqstp->rq_resp;

	xdr_ressize_check(rqstp, p);
	p = resp->buffer;
	*p++ = 0;			/* no more entries */
	*p++ = htonl((resp->common.err == nfserr_eof));
	rqstp->rq_res.page_len = (((unsigned long)p-1) & ~PAGE_MASK)+1;

	return 1;
}