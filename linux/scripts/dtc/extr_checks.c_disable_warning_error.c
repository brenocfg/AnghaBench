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
 int ARRAY_SIZE (struct check**) ; 
 struct check** check_table ; 

__attribute__((used)) static void disable_warning_error(struct check *c, bool warn, bool error)
{
	int i;

	/* Lowering level, also lower it for things this is the prereq
	 * for */
	if ((warn && c->warn) || (error && c->error)) {
		for (i = 0; i < ARRAY_SIZE(check_table); i++) {
			struct check *cc = check_table[i];
			int j;

			for (j = 0; j < cc->num_prereqs; j++)
				if (cc->prereq[j] == c)
					disable_warning_error(cc, warn, error);
		}
	}

	c->warn = c->warn && !warn;
	c->error = c->error && !error;
}