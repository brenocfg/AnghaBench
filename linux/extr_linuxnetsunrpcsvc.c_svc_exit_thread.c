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
struct svc_serv {int dummy; } ;
struct svc_rqst {int /*<<< orphan*/  rq_all; int /*<<< orphan*/  rq_flags; struct svc_pool* rq_pool; struct svc_serv* rq_server; } ;
struct svc_pool {int /*<<< orphan*/  sp_lock; int /*<<< orphan*/  sp_nrthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_VICTIM ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_destroy (struct svc_serv*) ; 
 int /*<<< orphan*/  svc_rqst_free (struct svc_rqst*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
svc_exit_thread(struct svc_rqst *rqstp)
{
	struct svc_serv	*serv = rqstp->rq_server;
	struct svc_pool	*pool = rqstp->rq_pool;

	spin_lock_bh(&pool->sp_lock);
	pool->sp_nrthreads--;
	if (!test_and_set_bit(RQ_VICTIM, &rqstp->rq_flags))
		list_del_rcu(&rqstp->rq_all);
	spin_unlock_bh(&pool->sp_lock);

	svc_rqst_free(rqstp);

	/* Release the server */
	if (serv)
		svc_destroy(serv);
}