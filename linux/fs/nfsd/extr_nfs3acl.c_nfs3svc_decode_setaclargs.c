#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct kvec* head; } ;
struct svc_rqst {TYPE_1__ rq_arg; struct nfsd3_setaclargs* rq_argp; } ;
struct nfsd3_setaclargs {int mask; int /*<<< orphan*/  acl_default; int /*<<< orphan*/  acl_access; int /*<<< orphan*/  fh; } ;
struct kvec {scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS_ACL ; 
 int NFS_ACL_MASK ; 
 int NFS_DFACL ; 
 int /*<<< orphan*/ * nfs3svc_decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfsacl_decode (TYPE_1__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs3svc_decode_setaclargs(struct svc_rqst *rqstp, __be32 *p)
{
	struct nfsd3_setaclargs *args = rqstp->rq_argp;
	struct kvec *head = rqstp->rq_arg.head;
	unsigned int base;
	int n;

	p = nfs3svc_decode_fh(p, &args->fh);
	if (!p)
		return 0;
	args->mask = ntohl(*p++);
	if (args->mask & ~NFS_ACL_MASK ||
	    !xdr_argsize_check(rqstp, p))
		return 0;

	base = (char *)p - (char *)head->iov_base;
	n = nfsacl_decode(&rqstp->rq_arg, base, NULL,
			  (args->mask & NFS_ACL) ?
			  &args->acl_access : NULL);
	if (n > 0)
		n = nfsacl_decode(&rqstp->rq_arg, base + n, NULL,
				  (args->mask & NFS_DFACL) ?
				  &args->acl_default : NULL);
	return (n > 0);
}