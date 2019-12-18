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

/* Variables and functions */
 char* _ (char*) ; 
 char* cpuidle_get_driver () ; 
 char* cpuidle_get_governor () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void cpuidle_general_output(void)
{
	char *tmp;

	tmp = cpuidle_get_driver();
	if (!tmp) {
		printf(_("Could not determine cpuidle driver\n"));
		return;
	}

	printf(_("CPUidle driver: %s\n"), tmp);
	free(tmp);

	tmp = cpuidle_get_governor();
	if (!tmp) {
		printf(_("Could not determine cpuidle governor\n"));
		return;
	}

	printf(_("CPUidle governor: %s\n"), tmp);
	free(tmp);
}