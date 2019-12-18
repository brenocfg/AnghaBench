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
struct TYPE_2__ {scalar_t__ php_ini_path_override; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_1__ fuzzer_module ; 
 scalar_t__ strdup (char const*) ; 

void fuzzer_set_ini_file(const char *file)
{
	if (fuzzer_module.php_ini_path_override) {
		free(fuzzer_module.php_ini_path_override);
	}
	fuzzer_module.php_ini_path_override = strdup(file);
}