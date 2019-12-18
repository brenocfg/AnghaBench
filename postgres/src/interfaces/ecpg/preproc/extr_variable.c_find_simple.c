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
struct variable {int /*<<< orphan*/  name; struct variable* next; } ;

/* Variables and functions */
 struct variable* allvariables ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct variable *
find_simple(char *name)
{
	struct variable *p;

	for (p = allvariables; p; p = p->next)
	{
		if (strcmp(p->name, name) == 0)
			return p;
	}

	return NULL;
}