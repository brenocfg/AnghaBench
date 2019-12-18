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
struct fpm_scoreboard_s {unsigned int nprocs; int free_proc; TYPE_1__** procs; } ;
struct fpm_scoreboard_proc_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void fpm_scoreboard_proc_free(struct fpm_scoreboard_s *scoreboard, int child_index) /* {{{ */
{
	if (!scoreboard) {
		return;
	}

	if (child_index < 0 || (unsigned int)child_index >= scoreboard->nprocs) {
		return;
	}

	if (scoreboard->procs[child_index] && scoreboard->procs[child_index]->used > 0) {
		memset(scoreboard->procs[child_index], 0, sizeof(struct fpm_scoreboard_proc_s));
	}

	/* set this slot as free to avoid search on next alloc */
	scoreboard->free_proc = child_index;
}