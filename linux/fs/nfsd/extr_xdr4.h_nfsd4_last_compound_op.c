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
struct nfsd4_compoundres {scalar_t__ opcnt; } ;
struct nfsd4_compoundargs {scalar_t__ opcnt; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nfsd4_last_compound_op(struct svc_rqst *rqstp)
{
	struct nfsd4_compoundres *resp = rqstp->rq_resp;
	struct nfsd4_compoundargs *argp = rqstp->rq_argp;

	return argp->opcnt == resp->opcnt;
}