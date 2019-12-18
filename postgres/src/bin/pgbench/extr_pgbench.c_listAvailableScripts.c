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
struct TYPE_3__ {char* name; char* desc; } ;

/* Variables and functions */
 TYPE_1__* builtin_script ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int lengthof (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
listAvailableScripts(void)
{
	int			i;

	fprintf(stderr, "Available builtin scripts:\n");
	for (i = 0; i < lengthof(builtin_script); i++)
		fprintf(stderr, "  %13s: %s\n", builtin_script[i].name, builtin_script[i].desc);
	fprintf(stderr, "\n");
}