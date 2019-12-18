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
struct TYPE_5__ {int /*<<< orphan*/ * splan; scalar_t__ nplans; int /*<<< orphan*/  ident; } ;
typedef  TYPE_1__ EPlan ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static EPlan *
find_plan(char *ident, EPlan **eplan, int *nplans)
{
	EPlan	   *newp;
	int			i;

	if (*nplans > 0)
	{
		for (i = 0; i < *nplans; i++)
		{
			if (strcmp((*eplan)[i].ident, ident) == 0)
				break;
		}
		if (i != *nplans)
			return (*eplan + i);
		*eplan = (EPlan *) realloc(*eplan, (i + 1) * sizeof(EPlan));
		newp = *eplan + i;
	}
	else
	{
		newp = *eplan = (EPlan *) malloc(sizeof(EPlan));
		(*nplans) = i = 0;
	}

	newp->ident = strdup(ident);
	newp->nplans = 0;
	newp->splan = NULL;
	(*nplans)++;

	return newp;
}