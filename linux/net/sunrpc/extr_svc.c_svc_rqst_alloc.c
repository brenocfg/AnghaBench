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
struct svc_serv {int /*<<< orphan*/  sv_max_mesg; int /*<<< orphan*/  sv_xdrsize; } ;
struct svc_rqst {void* rq_resp; void* rq_argp; struct svc_pool* rq_pool; struct svc_serv* rq_server; int /*<<< orphan*/  rq_lock; int /*<<< orphan*/  rq_flags; } ;
struct svc_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RQ_BUSY ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* kmalloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct svc_rqst* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_init_buffer (struct svc_rqst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svc_rqst_free (struct svc_rqst*) ; 

struct svc_rqst *
svc_rqst_alloc(struct svc_serv *serv, struct svc_pool *pool, int node)
{
	struct svc_rqst	*rqstp;

	rqstp = kzalloc_node(sizeof(*rqstp), GFP_KERNEL, node);
	if (!rqstp)
		return rqstp;

	__set_bit(RQ_BUSY, &rqstp->rq_flags);
	spin_lock_init(&rqstp->rq_lock);
	rqstp->rq_server = serv;
	rqstp->rq_pool = pool;

	rqstp->rq_argp = kmalloc_node(serv->sv_xdrsize, GFP_KERNEL, node);
	if (!rqstp->rq_argp)
		goto out_enomem;

	rqstp->rq_resp = kmalloc_node(serv->sv_xdrsize, GFP_KERNEL, node);
	if (!rqstp->rq_resp)
		goto out_enomem;

	if (!svc_init_buffer(rqstp, serv->sv_max_mesg, node))
		goto out_enomem;

	return rqstp;
out_enomem:
	svc_rqst_free(rqstp);
	return NULL;
}