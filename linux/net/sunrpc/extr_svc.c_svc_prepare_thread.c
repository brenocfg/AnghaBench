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
struct svc_serv {int /*<<< orphan*/  sv_nrthreads; } ;
struct svc_rqst {int /*<<< orphan*/  rq_all; } ;
struct svc_pool {int /*<<< orphan*/  sp_lock; int /*<<< orphan*/  sp_all_threads; int /*<<< orphan*/  sp_nrthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct svc_rqst* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct svc_rqst* svc_rqst_alloc (struct svc_serv*,struct svc_pool*,int) ; 

struct svc_rqst *
svc_prepare_thread(struct svc_serv *serv, struct svc_pool *pool, int node)
{
	struct svc_rqst	*rqstp;

	rqstp = svc_rqst_alloc(serv, pool, node);
	if (!rqstp)
		return ERR_PTR(-ENOMEM);

	serv->sv_nrthreads++;
	spin_lock_bh(&pool->sp_lock);
	pool->sp_nrthreads++;
	list_add_rcu(&rqstp->rq_all, &pool->sp_all_threads);
	spin_unlock_bh(&pool->sp_lock);
	return rqstp;
}