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
struct svc_rqst {struct nlm_args* rq_argp; } ;
struct TYPE_3__ {int /*<<< orphan*/  fl_type; } ;
struct TYPE_4__ {TYPE_1__ fl; } ;
struct nlm_args {int monitor; void* state; void* reclaim; TYPE_2__ lock; void* block; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/ * nlm_decode_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm_decode_lock (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nlmsvc_decode_lockargs(struct svc_rqst *rqstp, __be32 *p)
{
	struct nlm_args *argp = rqstp->rq_argp;
	u32	exclusive;

	if (!(p = nlm_decode_cookie(p, &argp->cookie)))
		return 0;
	argp->block  = ntohl(*p++);
	exclusive    = ntohl(*p++);
	if (!(p = nlm_decode_lock(p, &argp->lock)))
		return 0;
	if (exclusive)
		argp->lock.fl.fl_type = F_WRLCK;
	argp->reclaim = ntohl(*p++);
	argp->state   = ntohl(*p++);
	argp->monitor = 1;		/* monitor client by default */

	return xdr_argsize_check(rqstp, p);
}