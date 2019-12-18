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
struct fpm_scoreboard_s {int idle; int active; int lq; int lq_len; int lq_max; int requests; int max_children_reached; int slow_rq; int active_max; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int FPM_SCOREBOARD_ACTION_SET ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 struct fpm_scoreboard_s* fpm_scoreboard ; 
 int /*<<< orphan*/  fpm_spinlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

void fpm_scoreboard_update(int idle, int active, int lq, int lq_len, int requests, int max_children_reached, int slow_rq, int action, struct fpm_scoreboard_s *scoreboard) /* {{{ */
{
	if (!scoreboard) {
		scoreboard = fpm_scoreboard;
	}
	if (!scoreboard) {
		zlog(ZLOG_WARNING, "Unable to update scoreboard: the SHM has not been found");
		return;
	}


	fpm_spinlock(&scoreboard->lock, 0);
	if (action == FPM_SCOREBOARD_ACTION_SET) {
		if (idle >= 0) {
			scoreboard->idle = idle;
		}
		if (active >= 0) {
			scoreboard->active = active;
		}
		if (lq >= 0) {
			scoreboard->lq = lq;
		}
		if (lq_len >= 0) {
			scoreboard->lq_len = lq_len;
		}
#ifdef HAVE_FPM_LQ /* prevent unnecessary test */
		if (scoreboard->lq > scoreboard->lq_max) {
			scoreboard->lq_max = scoreboard->lq;
		}
#endif
		if (requests >= 0) {
			scoreboard->requests = requests;
		}

		if (max_children_reached >= 0) {
			scoreboard->max_children_reached = max_children_reached;
		}
		if (slow_rq > 0) {
			scoreboard->slow_rq = slow_rq;
		}
	} else {
		if (scoreboard->idle + idle > 0) {
			scoreboard->idle += idle;
		} else {
			scoreboard->idle = 0;
		}

		if (scoreboard->active + active > 0) {
			scoreboard->active += active;
		} else {
			scoreboard->active = 0;
		}

		if (scoreboard->requests + requests > 0) {
			scoreboard->requests += requests;
		} else {
			scoreboard->requests = 0;
		}

		if (scoreboard->max_children_reached + max_children_reached > 0) {
			scoreboard->max_children_reached += max_children_reached;
		} else {
			scoreboard->max_children_reached = 0;
		}

		if (scoreboard->slow_rq + slow_rq > 0) {
			scoreboard->slow_rq += slow_rq;
		} else {
			scoreboard->slow_rq = 0;
		}
	}

	if (scoreboard->active > scoreboard->active_max) {
		scoreboard->active_max = scoreboard->active;
	}

	fpm_unlock(scoreboard->lock);
}