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
struct config_generic {int dummy; } ;
typedef  int /*<<< orphan*/  mixedStruct ;

/* Variables and functions */
 int GetNumConfigOptions () ; 
 int /*<<< orphan*/  build_guc_variables () ; 
 scalar_t__ displayStruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct config_generic** get_guc_variables () ; 
 int /*<<< orphan*/  printMixedStruct (int /*<<< orphan*/ *) ; 

void
GucInfoMain(void)
{
	struct config_generic **guc_vars;
	int			numOpts,
				i;

	/* Initialize the guc_variables[] array */
	build_guc_variables();

	guc_vars = get_guc_variables();
	numOpts = GetNumConfigOptions();

	for (i = 0; i < numOpts; i++)
	{
		mixedStruct *var = (mixedStruct *) guc_vars[i];

		if (displayStruct(var))
			printMixedStruct(var);
	}

	exit(0);
}