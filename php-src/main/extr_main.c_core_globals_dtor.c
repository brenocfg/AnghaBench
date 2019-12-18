#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ php_binary; scalar_t__ disable_classes; scalar_t__ disable_functions; scalar_t__ last_error_file; scalar_t__ last_error_message; } ;
typedef  TYPE_1__ php_core_globals ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  php_shutdown_ticks () ; 

__attribute__((used)) static void core_globals_dtor(php_core_globals *core_globals)
{
	if (core_globals->last_error_message) {
		free(core_globals->last_error_message);
	}
	if (core_globals->last_error_file) {
		free(core_globals->last_error_file);
	}
	if (core_globals->disable_functions) {
		free(core_globals->disable_functions);
	}
	if (core_globals->disable_classes) {
		free(core_globals->disable_classes);
	}
	if (core_globals->php_binary) {
		free(core_globals->php_binary);
	}

	php_shutdown_ticks();
}