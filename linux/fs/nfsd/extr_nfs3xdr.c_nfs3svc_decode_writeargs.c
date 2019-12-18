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
typedef  void* u32 ;
struct TYPE_3__ {unsigned int page_len; struct kvec* tail; struct kvec* head; } ;
struct svc_rqst {TYPE_1__ rq_arg; struct nfsd3_writeargs* rq_argp; } ;
struct TYPE_4__ {unsigned int iov_len; void* iov_base; } ;
struct nfsd3_writeargs {void* count; unsigned int len; TYPE_2__ first; void* stable; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
struct kvec {void* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int XDR_QUADLEN (unsigned int) ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* svc_max_payload (struct svc_rqst*) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nfs3svc_decode_writeargs(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_writeargs *args = rqstp->rq_argp;
	unsigned int len, hdr, dlen;
	u32 max_blocksize = svc_max_payload(rqstp);
	struct kvec *head = rqstp->rq_arg.head;
	struct kvec *tail = rqstp->rq_arg.tail;

	p = decode_fh(p, &args->fh);
	if (!p)
		return 0;
	p = xdr_decode_hyper(p, &args->offset);

	args->count = ntohl(*p++);
	args->stable = ntohl(*p++);
	len = args->len = ntohl(*p++);
	if ((void *)p > head->iov_base + head->iov_len)
		return 0;
	/*
	 * The count must equal the amount of data passed.
	 */
	if (args->count != args->len)
		return 0;

	/*
	 * Check to make sure that we got the right number of
	 * bytes.
	 */
	hdr = (void*)p - head->iov_base;
	dlen = head->iov_len + rqstp->rq_arg.page_len + tail->iov_len - hdr;
	/*
	 * Round the length of the data which was specified up to
	 * the next multiple of XDR units and then compare that
	 * against the length which was actually received.
	 * Note that when RPCSEC/GSS (for example) is used, the
	 * data buffer can be padded so dlen might be larger
	 * than required.  It must never be smaller.
	 */
	if (dlen < XDR_QUADLEN(len)*4)
		return 0;

	if (args->count > max_blocksize) {
		args->count = max_blocksize;
		len = args->len = max_blocksize;
	}

	args->first.iov_base = (void *)p;
	args->first.iov_len = head->iov_len - hdr;
	return 1;
}