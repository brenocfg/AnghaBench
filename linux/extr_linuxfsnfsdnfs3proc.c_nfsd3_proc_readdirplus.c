#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {struct page** rq_next_page; struct page** rq_respages; struct nfsd3_readdirres* rq_resp; struct nfsd3_readdirargs* rq_argp; } ;
struct page {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  err; } ;
struct TYPE_7__ {TYPE_1__* fh_export; } ;
struct nfsd3_readdirres {int count; int buflen; void** offset; void** offset1; scalar_t__ buffer; int /*<<< orphan*/  verf; TYPE_3__ common; TYPE_2__ fh; struct svc_rqst* rqstp; } ;
struct nfsd3_readdirargs {int count; int cookie; int /*<<< orphan*/  verf; scalar_t__ buffer; int /*<<< orphan*/  fh; } ;
typedef  int loff_t ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_6__ {int ex_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int NFSEXP_NOREADDIRPLUS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  RETURN_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ fh_verify (struct svc_rqst*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs3svc_encode_entry_plus ; 
 int /*<<< orphan*/  nfs_ok ; 
 scalar_t__ nfsd_readdir (struct svc_rqst*,TYPE_2__*,int*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_notsupp ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ unlikely (void**) ; 
 int /*<<< orphan*/  xdr_encode_hyper (void**,int) ; 

__attribute__((used)) static __be32
nfsd3_proc_readdirplus(struct svc_rqst *rqstp)
{
	struct nfsd3_readdirargs *argp = rqstp->rq_argp;
	struct nfsd3_readdirres  *resp = rqstp->rq_resp;
	__be32	nfserr;
	int	count = 0;
	loff_t	offset;
	struct page **p;
	caddr_t	page_addr = NULL;

	dprintk("nfsd: READDIR+(3) %s %d bytes at %d\n",
				SVCFH_fmt(&argp->fh),
				argp->count, (u32) argp->cookie);

	/* Convert byte count to number of words (i.e. >> 2),
	 * and reserve room for the NULL ptr & eof flag (-2 words) */
	resp->count = (argp->count >> 2) - 2;

	/* Read directory and encode entries on the fly */
	fh_copy(&resp->fh, &argp->fh);

	resp->common.err = nfs_ok;
	resp->buffer = argp->buffer;
	resp->buflen = resp->count;
	resp->rqstp = rqstp;
	offset = argp->cookie;

	nfserr = fh_verify(rqstp, &resp->fh, S_IFDIR, NFSD_MAY_NOP);
	if (nfserr)
		RETURN_STATUS(nfserr);

	if (resp->fh.fh_export->ex_flags & NFSEXP_NOREADDIRPLUS)
		RETURN_STATUS(nfserr_notsupp);

	nfserr = nfsd_readdir(rqstp, &resp->fh,
				     &offset,
				     &resp->common,
				     nfs3svc_encode_entry_plus);
	memcpy(resp->verf, argp->verf, 8);
	for (p = rqstp->rq_respages + 1; p < rqstp->rq_next_page; p++) {
		page_addr = page_address(*p);

		if (((caddr_t)resp->buffer >= page_addr) &&
		    ((caddr_t)resp->buffer < page_addr + PAGE_SIZE)) {
			count += (caddr_t)resp->buffer - page_addr;
			break;
		}
		count += PAGE_SIZE;
	}
	resp->count = count >> 2;
	if (resp->offset) {
		if (unlikely(resp->offset1)) {
			/* we ended up with offset on a page boundary */
			*resp->offset = htonl(offset >> 32);
			*resp->offset1 = htonl(offset & 0xffffffff);
			resp->offset1 = NULL;
		} else {
			xdr_encode_hyper(resp->offset, offset);
		}
		resp->offset = NULL;
	}

	RETURN_STATUS(nfserr);
}