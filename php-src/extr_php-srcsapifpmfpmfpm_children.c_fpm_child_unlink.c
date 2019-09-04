#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fpm_child_s {TYPE_1__* prev; TYPE_3__* next; TYPE_2__* wp; } ;
struct TYPE_8__ {int /*<<< orphan*/  running_children; } ;
struct TYPE_7__ {TYPE_1__* prev; } ;
struct TYPE_6__ {TYPE_3__* children; int /*<<< orphan*/  running_children; } ;
struct TYPE_5__ {TYPE_3__* next; } ;

/* Variables and functions */
 TYPE_4__ fpm_globals ; 

__attribute__((used)) static void fpm_child_unlink(struct fpm_child_s *child) /* {{{ */
{
	--child->wp->running_children;
	--fpm_globals.running_children;

	if (child->prev) {
		child->prev->next = child->next;
	} else {
		child->wp->children = child->next;
	}

	if (child->next) {
		child->next->prev = child->prev;
	}
}