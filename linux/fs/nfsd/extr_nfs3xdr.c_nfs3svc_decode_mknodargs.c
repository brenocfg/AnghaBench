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
struct svc_rqst {struct nfsd3_mknodargs* rq_argp; } ;
struct nfsd3_mknodargs {scalar_t__ ftype; void* minor; void* major; int /*<<< orphan*/  attrs; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NF3BLK ; 
 scalar_t__ NF3CHR ; 
 scalar_t__ NF3FIFO ; 
 scalar_t__ NF3SOCK ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decode_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decode_sattr3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_user_namespace (struct svc_rqst*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfs3svc_decode_mknodargs(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_mknodargs *args = rqstp->rq_argp;

	if (!(p = decode_fh(p, &args->fh))
	 || !(p = decode_filename(p, &args->name, &args->len)))
		return 0;

	args->ftype = ntohl(*p++);

	if (args->ftype == NF3BLK  || args->ftype == NF3CHR
	 || args->ftype == NF3SOCK || args->ftype == NF3FIFO)
		p = decode_sattr3(p, &args->attrs, nfsd_user_namespace(rqstp));

	if (args->ftype == NF3BLK || args->ftype == NF3CHR) {
		args->major = ntohl(*p++);
		args->minor = ntohl(*p++);
	}

	return xdr_argsize_check(rqstp, p);
}