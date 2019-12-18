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
struct fpm_worker_pool_s {struct fpm_child_s* children; struct fpm_worker_pool_s* next; } ;
struct fpm_child_s {scalar_t__ pid; TYPE_2__* wp; struct fpm_child_s* next; } ;
struct TYPE_4__ {TYPE_1__* config; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 char** fpm_signal_names ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int kill (scalar_t__,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int,...) ; 

void fpm_pctl_kill_all(int signo) /* {{{ */
{
	struct fpm_worker_pool_s *wp;
	int alive_children = 0;

	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		struct fpm_child_s *child;

		for (child = wp->children; child; child = child->next) {
			int res = kill(child->pid, signo);

			zlog(ZLOG_DEBUG, "[pool %s] sending signal %d %s to child %d",
				child->wp->config->name, signo,
				fpm_signal_names[signo] ? fpm_signal_names[signo] : "", (int) child->pid);

			if (res == 0) {
				++alive_children;
			}
		}
	}

	if (alive_children) {
		zlog(ZLOG_DEBUG, "%d child(ren) still alive", alive_children);
	}
}