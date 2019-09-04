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
struct svc_rqst {struct nfsd4_compoundargs* rq_argp; struct nfsd4_compoundres* rq_resp; } ;
struct nfsd4_operation {int op_flags; } ;
struct nfsd4_op {scalar_t__ opnum; } ;
struct nfsd4_compoundres {int opcnt; } ;
struct nfsd4_compoundargs {size_t opcnt; struct nfsd4_op* ops; } ;

/* Variables and functions */
 struct nfsd4_operation* OPDESC (struct nfsd4_op*) ; 
 int OP_HANDLES_WRONGSEC ; 
 scalar_t__ OP_ILLEGAL ; 
 int OP_IS_PUTFH_LIKE ; 

__attribute__((used)) static bool need_wrongsec_check(struct svc_rqst *rqstp)
{
	struct nfsd4_compoundres *resp = rqstp->rq_resp;
	struct nfsd4_compoundargs *argp = rqstp->rq_argp;
	struct nfsd4_op *this = &argp->ops[resp->opcnt - 1];
	struct nfsd4_op *next = &argp->ops[resp->opcnt];
	const struct nfsd4_operation *thisd = OPDESC(this);
	const struct nfsd4_operation *nextd;

	/*
	 * Most ops check wronsec on our own; only the putfh-like ops
	 * have special rules.
	 */
	if (!(thisd->op_flags & OP_IS_PUTFH_LIKE))
		return false;
	/*
	 * rfc 5661 2.6.3.1.1.6: don't bother erroring out a
	 * put-filehandle operation if we're not going to use the
	 * result:
	 */
	if (argp->opcnt == resp->opcnt)
		return false;
	if (next->opnum == OP_ILLEGAL)
		return false;
	nextd = OPDESC(next);
	/*
	 * Rest of 2.6.3.1.1: certain operations will return WRONGSEC
	 * errors themselves as necessary; others should check for them
	 * now:
	 */
	return !(nextd->op_flags & OP_HANDLES_WRONGSEC);
}