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
struct fpm_worker_pool_s {int /*<<< orphan*/  scoreboard; TYPE_1__* config; } ;
struct fpm_child_s {int fd_stdout; int fd_stderr; int /*<<< orphan*/  scoreboard_i; struct fpm_worker_pool_s* wp; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_ERROR ; 
 struct fpm_child_s* fpm_child_alloc () ; 
 int /*<<< orphan*/  fpm_child_free (struct fpm_child_s*) ; 
 scalar_t__ fpm_scoreboard_proc_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpm_stdio_discard_pipes (struct fpm_child_s*) ; 
 scalar_t__ fpm_stdio_prepare_pipes (struct fpm_child_s*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fpm_child_s *fpm_resources_prepare(struct fpm_worker_pool_s *wp) /* {{{ */
{
	struct fpm_child_s *c;

	c = fpm_child_alloc();

	if (!c) {
		zlog(ZLOG_ERROR, "[pool %s] unable to malloc new child", wp->config->name);
		return 0;
	}

	c->wp = wp;
	c->fd_stdout = -1; c->fd_stderr = -1;

	if (0 > fpm_stdio_prepare_pipes(c)) {
		fpm_child_free(c);
		return 0;
	}

	if (0 > fpm_scoreboard_proc_alloc(wp->scoreboard, &c->scoreboard_i)) {
		fpm_stdio_discard_pipes(c);
		fpm_child_free(c);
		return 0;
	}

	return c;
}