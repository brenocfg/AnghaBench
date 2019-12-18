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
struct fpm_scoreboard_s {unsigned int nprocs; struct fpm_scoreboard_proc_s** procs; } ;
struct fpm_scoreboard_proc_s {int dummy; } ;

/* Variables and functions */
 struct fpm_scoreboard_s* fpm_scoreboard ; 
 int fpm_scoreboard_i ; 

struct fpm_scoreboard_proc_s *fpm_scoreboard_proc_get(struct fpm_scoreboard_s *scoreboard, int child_index) /* {{{*/
{
	if (!scoreboard) {
		scoreboard = fpm_scoreboard;
	}

	if (!scoreboard) {
		return NULL;
	}

	if (child_index < 0) {
		child_index = fpm_scoreboard_i;
	}

	if (child_index < 0 || (unsigned int)child_index >= scoreboard->nprocs) {
		return NULL;
	}

	return scoreboard->procs[child_index];
}