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
struct fpm_scoreboard_s {int nprocs; } ;
struct fpm_scoreboard_proc_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  fpm_shm_free (struct fpm_scoreboard_s*,size_t) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

void fpm_scoreboard_free(struct fpm_scoreboard_s *scoreboard) /* {{{ */
{
	size_t scoreboard_size, scoreboard_nprocs_size;

	if (!scoreboard) {
		zlog(ZLOG_ERROR, "**scoreboard is NULL");
		return;
	}

	scoreboard_size        = sizeof(struct fpm_scoreboard_s) + (scoreboard->nprocs) * sizeof(struct fpm_scoreboard_proc_s *);
	scoreboard_nprocs_size = sizeof(struct fpm_scoreboard_proc_s) * scoreboard->nprocs;

	fpm_shm_free(scoreboard, scoreboard_size + scoreboard_nprocs_size);
}