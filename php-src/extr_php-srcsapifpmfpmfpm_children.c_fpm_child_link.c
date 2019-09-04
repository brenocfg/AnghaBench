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
struct fpm_worker_pool_s {struct fpm_child_s* children; int /*<<< orphan*/  running_children; } ;
struct fpm_child_s {struct fpm_child_s* prev; struct fpm_child_s* next; struct fpm_worker_pool_s* wp; } ;
struct TYPE_2__ {int /*<<< orphan*/  running_children; } ;

/* Variables and functions */
 TYPE_1__ fpm_globals ; 

__attribute__((used)) static void fpm_child_link(struct fpm_child_s *child) /* {{{ */
{
	struct fpm_worker_pool_s *wp = child->wp;

	++wp->running_children;
	++fpm_globals.running_children;

	child->next = wp->children;
	if (child->next) {
		child->next->prev = child;
	}
	child->prev = 0;
	wp->children = child;
}