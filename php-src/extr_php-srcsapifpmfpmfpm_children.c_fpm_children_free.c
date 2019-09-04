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
struct fpm_child_s {struct fpm_child_s* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpm_child_close (struct fpm_child_s*,int /*<<< orphan*/ ) ; 

int fpm_children_free(struct fpm_child_s *child) /* {{{ */
{
	struct fpm_child_s *next;

	for (; child; child = next) {
		next = child->next;
		fpm_child_close(child, 0 /* in_event_loop */);
	}

	return 0;
}