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
struct svcxdr_tmpbuf {struct svcxdr_tmpbuf* next; } ;
struct svc_rqst {struct nfsd4_compoundargs* rq_argp; } ;
struct nfsd4_compoundargs {scalar_t__ ops; scalar_t__ iops; struct svcxdr_tmpbuf* to_free; struct svcxdr_tmpbuf* tmpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct svcxdr_tmpbuf*) ; 

void nfsd4_release_compoundargs(struct svc_rqst *rqstp)
{
	struct nfsd4_compoundargs *args = rqstp->rq_argp;

	if (args->ops != args->iops) {
		kfree(args->ops);
		args->ops = args->iops;
	}
	kfree(args->tmpp);
	args->tmpp = NULL;
	while (args->to_free) {
		struct svcxdr_tmpbuf *tb = args->to_free;
		args->to_free = tb->next;
		kfree(tb);
	}
}