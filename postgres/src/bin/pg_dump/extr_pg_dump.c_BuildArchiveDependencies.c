#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ reqs; int nDeps; int /*<<< orphan*/ * dependencies; int /*<<< orphan*/  dumpId; struct TYPE_7__* next; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_9__ {TYPE_1__* toc; } ;
struct TYPE_8__ {scalar_t__ nDeps; } ;
typedef  TYPE_2__ DumpableObject ;
typedef  int /*<<< orphan*/  DumpId ;
typedef  TYPE_3__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  findDumpableDependencies (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ **,int*,int*) ; 
 TYPE_2__* findObjectByDumpId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
BuildArchiveDependencies(Archive *fout)
{
	ArchiveHandle *AH = (ArchiveHandle *) fout;
	TocEntry   *te;

	/* Scan all TOC entries in the archive */
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		DumpableObject *dobj;
		DumpId	   *dependencies;
		int			nDeps;
		int			allocDeps;

		/* No need to process entries that will not be dumped */
		if (te->reqs == 0)
			continue;
		/* Ignore entries that already have "special" dependencies */
		if (te->nDeps > 0)
			continue;
		/* Otherwise, look up the item's original DumpableObject, if any */
		dobj = findObjectByDumpId(te->dumpId);
		if (dobj == NULL)
			continue;
		/* No work if it has no dependencies */
		if (dobj->nDeps <= 0)
			continue;
		/* Set up work array */
		allocDeps = 64;
		dependencies = (DumpId *) pg_malloc(allocDeps * sizeof(DumpId));
		nDeps = 0;
		/* Recursively find all dumpable dependencies */
		findDumpableDependencies(AH, dobj,
								 &dependencies, &nDeps, &allocDeps);
		/* And save 'em ... */
		if (nDeps > 0)
		{
			dependencies = (DumpId *) pg_realloc(dependencies,
												 nDeps * sizeof(DumpId));
			te->dependencies = dependencies;
			te->nDeps = nDeps;
		}
		else
			free(dependencies);
	}
}