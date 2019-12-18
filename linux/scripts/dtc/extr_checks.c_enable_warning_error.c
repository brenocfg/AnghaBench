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
struct check {int warn; int error; int num_prereqs; struct check** prereq; } ;

/* Variables and functions */

__attribute__((used)) static void enable_warning_error(struct check *c, bool warn, bool error)
{
	int i;

	/* Raising level, also raise it for prereqs */
	if ((warn && !c->warn) || (error && !c->error))
		for (i = 0; i < c->num_prereqs; i++)
			enable_warning_error(c->prereq[i], warn, error);

	c->warn = c->warn || warn;
	c->error = c->error || error;
}