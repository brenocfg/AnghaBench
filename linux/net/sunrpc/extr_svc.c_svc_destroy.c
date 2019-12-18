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
struct svc_serv {scalar_t__ sv_nrthreads; struct svc_serv* sv_pools; int /*<<< orphan*/  sv_tempsocks; int /*<<< orphan*/  sv_permsocks; int /*<<< orphan*/  sv_temptimer; TYPE_1__* sv_program; } ;
struct TYPE_2__ {int /*<<< orphan*/  pg_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cache_clean_deferred (struct svc_serv*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct svc_serv*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,struct svc_serv*) ; 
 int /*<<< orphan*/  svc_pool_map_put () ; 
 scalar_t__ svc_serv_is_pooled (struct svc_serv*) ; 
 int /*<<< orphan*/  svc_sock_update_bufs (struct svc_serv*) ; 

void
svc_destroy(struct svc_serv *serv)
{
	dprintk("svc: svc_destroy(%s, %d)\n",
				serv->sv_program->pg_name,
				serv->sv_nrthreads);

	if (serv->sv_nrthreads) {
		if (--(serv->sv_nrthreads) != 0) {
			svc_sock_update_bufs(serv);
			return;
		}
	} else
		printk("svc_destroy: no threads for serv=%p!\n", serv);

	del_timer_sync(&serv->sv_temptimer);

	/*
	 * The last user is gone and thus all sockets have to be destroyed to
	 * the point. Check this.
	 */
	BUG_ON(!list_empty(&serv->sv_permsocks));
	BUG_ON(!list_empty(&serv->sv_tempsocks));

	cache_clean_deferred(serv);

	if (svc_serv_is_pooled(serv))
		svc_pool_map_put();

	kfree(serv->sv_pools);
	kfree(serv);
}