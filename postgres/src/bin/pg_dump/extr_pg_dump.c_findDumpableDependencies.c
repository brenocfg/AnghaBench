#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ objType; int nDeps; int /*<<< orphan*/ * dependencies; } ;
typedef  TYPE_1__ DumpableObject ;
typedef  int /*<<< orphan*/  DumpId ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 scalar_t__ DO_POST_DATA_BOUNDARY ; 
 scalar_t__ DO_PRE_DATA_BOUNDARY ; 
 scalar_t__ TocIDRequired (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* findObjectByDumpId (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
findDumpableDependencies(ArchiveHandle *AH, DumpableObject *dobj,
						 DumpId **dependencies, int *nDeps, int *allocDeps)
{
	int			i;

	/*
	 * Ignore section boundary objects: if we search through them, we'll
	 * report lots of bogus dependencies.
	 */
	if (dobj->objType == DO_PRE_DATA_BOUNDARY ||
		dobj->objType == DO_POST_DATA_BOUNDARY)
		return;

	for (i = 0; i < dobj->nDeps; i++)
	{
		DumpId		depid = dobj->dependencies[i];

		if (TocIDRequired(AH, depid) != 0)
		{
			/* Object will be dumped, so just reference it as a dependency */
			if (*nDeps >= *allocDeps)
			{
				*allocDeps *= 2;
				*dependencies = (DumpId *) pg_realloc(*dependencies,
													  *allocDeps * sizeof(DumpId));
			}
			(*dependencies)[*nDeps] = depid;
			(*nDeps)++;
		}
		else
		{
			/*
			 * Object will not be dumped, so recursively consider its deps. We
			 * rely on the assumption that sortDumpableObjects already broke
			 * any dependency loops, else we might recurse infinitely.
			 */
			DumpableObject *otherdobj = findObjectByDumpId(depid);

			if (otherdobj)
				findDumpableDependencies(AH, otherdobj,
										 dependencies, nDeps, allocDeps);
		}
	}
}