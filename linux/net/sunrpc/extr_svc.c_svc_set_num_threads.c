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
struct svc_serv {int sv_nrthreads; } ;
struct svc_pool {int /*<<< orphan*/  sp_lock; scalar_t__ sp_nrthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int svc_signal_kthreads (struct svc_serv*,struct svc_pool*,int) ; 
 int svc_start_kthreads (struct svc_serv*,struct svc_pool*,int) ; 

int
svc_set_num_threads(struct svc_serv *serv, struct svc_pool *pool, int nrservs)
{
	if (pool == NULL) {
		/* The -1 assumes caller has done a svc_get() */
		nrservs -= (serv->sv_nrthreads-1);
	} else {
		spin_lock_bh(&pool->sp_lock);
		nrservs -= pool->sp_nrthreads;
		spin_unlock_bh(&pool->sp_lock);
	}

	if (nrservs > 0)
		return svc_start_kthreads(serv, pool, nrservs);
	if (nrservs < 0)
		return svc_signal_kthreads(serv, pool, nrservs);
	return 0;
}