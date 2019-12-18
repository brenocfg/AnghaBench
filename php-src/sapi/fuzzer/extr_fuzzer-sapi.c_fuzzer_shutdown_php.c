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
struct TYPE_2__ {int /*<<< orphan*/  ini_entries; } ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__ fuzzer_module ; 
 int /*<<< orphan*/  php_module_shutdown () ; 
 int /*<<< orphan*/  sapi_shutdown () ; 

int fuzzer_shutdown_php()
{
	php_module_shutdown();
	sapi_shutdown();

	free(fuzzer_module.ini_entries);
	return SUCCESS;
}