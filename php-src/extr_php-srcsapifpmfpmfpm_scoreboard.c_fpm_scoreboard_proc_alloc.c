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
struct fpm_scoreboard_s {size_t free_proc; unsigned int nprocs; TYPE_1__** procs; int /*<<< orphan*/  pool; } ;
struct TYPE_2__ {int used; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int fpm_scoreboard_proc_alloc(struct fpm_scoreboard_s *scoreboard, int *child_index) /* {{{ */
{
	int i = -1;

	if (!scoreboard || !child_index) {
		return -1;
	}

	/* first try the slot which is supposed to be free */
	if (scoreboard->free_proc >= 0 && (unsigned int)scoreboard->free_proc < scoreboard->nprocs) {
		if (scoreboard->procs[scoreboard->free_proc] && !scoreboard->procs[scoreboard->free_proc]->used) {
			i = scoreboard->free_proc;
		}
	}

	if (i < 0) { /* the supposed free slot is not, let's search for a free slot */
		zlog(ZLOG_DEBUG, "[pool %s] the proc->free_slot was not free. Let's search", scoreboard->pool);
		for (i = 0; i < (int)scoreboard->nprocs; i++) {
			if (scoreboard->procs[i] && !scoreboard->procs[i]->used) { /* found */
				break;
			}
		}
	}

	/* no free slot */
	if (i < 0 || i >= (int)scoreboard->nprocs) {
		zlog(ZLOG_ERROR, "[pool %s] no free scoreboard slot", scoreboard->pool);
		return -1;
	}

	scoreboard->procs[i]->used = 1;
	*child_index = i;

	/* supposed next slot is free */
	if (i + 1 >= (int)scoreboard->nprocs) {
		scoreboard->free_proc = 0;
	} else {
		scoreboard->free_proc = i + 1;
	}

	return 0;
}