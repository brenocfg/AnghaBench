#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ BuiltinScript ;

/* Variables and functions */
 TYPE_1__* builtin_script ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int lengthof (TYPE_1__*) ; 
 int /*<<< orphan*/  listAvailableScripts () ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const BuiltinScript *
findBuiltin(const char *name)
{
	int			i,
				found = 0,
				len = strlen(name);
	const BuiltinScript *result = NULL;

	for (i = 0; i < lengthof(builtin_script); i++)
	{
		if (strncmp(builtin_script[i].name, name, len) == 0)
		{
			result = &builtin_script[i];
			found++;
		}
	}

	/* ok, unambiguous result */
	if (found == 1)
		return result;

	/* error cases */
	if (found == 0)
		fprintf(stderr, "no builtin script found for name \"%s\"\n", name);
	else						/* found > 1 */
		fprintf(stderr,
				"ambiguous builtin name: %d builtin scripts found for prefix \"%s\"\n", found, name);

	listAvailableScripts();
	exit(1);
}