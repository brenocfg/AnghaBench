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
struct TYPE_2__ {int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_CLEANUP_ALL ; 
 scalar_t__ fpm_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_pctl_cleanup ; 
 scalar_t__* malloc (int) ; 
 int saved_argc ; 
 scalar_t__* saved_argv ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 

int fpm_pctl_init_main() /* {{{ */
{
	int i;

	saved_argc = fpm_globals.argc;
	saved_argv = malloc(sizeof(char *) * (saved_argc + 1));

	if (!saved_argv) {
		return -1;
	}

	for (i = 0; i < saved_argc; i++) {
		saved_argv[i] = strdup(fpm_globals.argv[i]);

		if (!saved_argv[i]) {
			return -1;
		}
	}

	saved_argv[i] = 0;

	if (0 > fpm_cleanup_add(FPM_CLEANUP_ALL, fpm_pctl_cleanup, 0)) {
		return -1;
	}
	return 0;
}