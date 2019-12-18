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
struct fpm_child_s {int fd_stdout; int fd_stderr; int /*<<< orphan*/  ev_stderr; int /*<<< orphan*/  ev_stdout; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fpm_child_free (struct fpm_child_s*) ; 
 int /*<<< orphan*/  fpm_event_fire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fpm_child_close(struct fpm_child_s *child, int in_event_loop) /* {{{ */
{
	if (child->fd_stdout != -1) {
		if (in_event_loop) {
			fpm_event_fire(&child->ev_stdout);
		}
		if (child->fd_stdout != -1) {
			close(child->fd_stdout);
		}
	}

	if (child->fd_stderr != -1) {
		if (in_event_loop) {
			fpm_event_fire(&child->ev_stderr);
		}
		if (child->fd_stderr != -1) {
			close(child->fd_stderr);
		}
	}

	fpm_child_free(child);
}