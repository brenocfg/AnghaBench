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
struct fpm_worker_pool_s {TYPE_2__* config; TYPE_1__* scoreboard; struct fpm_worker_pool_s* next; } ;
struct fpm_scoreboard_s {int dummy; } ;
struct fpm_scoreboard_proc_s {int dummy; } ;
struct TYPE_4__ {int pm_max_children; int name; int /*<<< orphan*/  pm; } ;
struct TYPE_3__ {unsigned int nprocs; int /*<<< orphan*/  pool; int /*<<< orphan*/  start_epoch; int /*<<< orphan*/  pm; void** procs; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  _SC_CLK_TCK ; 
 int fpm_scoreboard_tick ; 
 void* fpm_shm_alloc (size_t) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int,int) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int) ; 

int fpm_scoreboard_init_main() /* {{{ */
{
	struct fpm_worker_pool_s *wp;
	unsigned int i;

#ifdef HAVE_TIMES
#if (defined(HAVE_SYSCONF) && defined(_SC_CLK_TCK))
	fpm_scoreboard_tick = sysconf(_SC_CLK_TCK);
#else /* _SC_CLK_TCK */
#ifdef HZ
	fpm_scoreboard_tick = HZ;
#else /* HZ */
	fpm_scoreboard_tick = 100;
#endif /* HZ */
#endif /* _SC_CLK_TCK */
	zlog(ZLOG_DEBUG, "got clock tick '%.0f'", fpm_scoreboard_tick);
#endif /* HAVE_TIMES */


	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		size_t scoreboard_size, scoreboard_nprocs_size;
		void *shm_mem;

		if (wp->config->pm_max_children < 1) {
			zlog(ZLOG_ERROR, "[pool %s] Unable to create scoreboard SHM because max_client is not set", wp->config->name);
			return -1;
		}

		if (wp->scoreboard) {
			zlog(ZLOG_ERROR, "[pool %s] Unable to create scoreboard SHM because it already exists", wp->config->name);
			return -1;
		}

		scoreboard_size        = sizeof(struct fpm_scoreboard_s) + (wp->config->pm_max_children) * sizeof(struct fpm_scoreboard_proc_s *);
		scoreboard_nprocs_size = sizeof(struct fpm_scoreboard_proc_s) * wp->config->pm_max_children;
		shm_mem                = fpm_shm_alloc(scoreboard_size + scoreboard_nprocs_size);

		if (!shm_mem) {
			return -1;
		}
		wp->scoreboard         = shm_mem;
		wp->scoreboard->nprocs = wp->config->pm_max_children;
		shm_mem               += scoreboard_size;

		for (i = 0; i < wp->scoreboard->nprocs; i++, shm_mem += sizeof(struct fpm_scoreboard_proc_s)) {
			wp->scoreboard->procs[i] = shm_mem;
		}

		wp->scoreboard->pm          = wp->config->pm;
		wp->scoreboard->start_epoch = time(NULL);
		strlcpy(wp->scoreboard->pool, wp->config->name, sizeof(wp->scoreboard->pool));
	}
	return 0;
}