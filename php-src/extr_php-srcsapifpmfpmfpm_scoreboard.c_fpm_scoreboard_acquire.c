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
struct fpm_scoreboard_s {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct fpm_scoreboard_s* fpm_scoreboard ; 
 int /*<<< orphan*/  fpm_spinlock (int /*<<< orphan*/ *,int) ; 

struct fpm_scoreboard_s *fpm_scoreboard_acquire(struct fpm_scoreboard_s *scoreboard, int nohang) /* {{{ */
{
	struct fpm_scoreboard_s *s;

	s = scoreboard ? scoreboard : fpm_scoreboard;
	if (!s) {
		return NULL;
	}

	if (!fpm_spinlock(&s->lock, nohang)) {
		return NULL;
	}
	return s;
}