#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ page_len; TYPE_2__* tail; TYPE_1__* head; } ;
struct svc_rqst {TYPE_3__ rq_arg; struct nfsd_symlinkargs* rq_argp; } ;
struct TYPE_8__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct nfsd_symlinkargs {scalar_t__ tlen; int /*<<< orphan*/  attrs; TYPE_4__ first; int /*<<< orphan*/  flen; int /*<<< orphan*/  fname; int /*<<< orphan*/  ffh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/ * iov_base; } ;
struct TYPE_5__ {int iov_len; } ;

/* Variables and functions */
 size_t XDR_QUADLEN (scalar_t__) ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decode_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_sattr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_user_namespace (struct svc_rqst*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

int
nfssvc_decode_symlinkargs(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd_symlinkargs *args = rqstp->rq_argp;
	char *base = (char *)p;
	size_t xdrlen;

	if (   !(p = decode_fh(p, &args->ffh))
	    || !(p = decode_filename(p, &args->fname, &args->flen)))
		return 0;

	args->tlen = ntohl(*p++);
	if (args->tlen == 0)
		return 0;

	args->first.iov_base = p;
	args->first.iov_len = rqstp->rq_arg.head[0].iov_len;
	args->first.iov_len -= (char *)p - base;

	/* This request is never larger than a page. Therefore,
	 * transport will deliver either:
	 * 1. pathname in the pagelist -> sattr is in the tail.
	 * 2. everything in the head buffer -> sattr is in the head.
	 */
	if (rqstp->rq_arg.page_len) {
		if (args->tlen != rqstp->rq_arg.page_len)
			return 0;
		p = rqstp->rq_arg.tail[0].iov_base;
	} else {
		xdrlen = XDR_QUADLEN(args->tlen);
		if (xdrlen > args->first.iov_len - (8 * sizeof(__be32)))
			return 0;
		p += xdrlen;
	}
	decode_sattr(p, &args->attrs, nfsd_user_namespace(rqstp));

	return 1;
}