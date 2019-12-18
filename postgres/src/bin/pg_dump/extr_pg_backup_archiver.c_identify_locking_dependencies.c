#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ section; int nDeps; size_t* dependencies; int nLockDeps; int /*<<< orphan*/  lockDeps; int /*<<< orphan*/  desc; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_8__ {size_t maxDumpId; TYPE_1__** tocsByDumpId; } ;
struct TYPE_6__ {int /*<<< orphan*/  desc; } ;
typedef  size_t DumpId ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ SECTION_POST_DATA ; 
 int /*<<< orphan*/  free (size_t*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  pg_realloc (size_t*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
identify_locking_dependencies(ArchiveHandle *AH, TocEntry *te)
{
	DumpId	   *lockids;
	int			nlockids;
	int			i;

	/*
	 * We only care about this for POST_DATA items.  PRE_DATA items are not
	 * run in parallel, and DATA items are all independent by assumption.
	 */
	if (te->section != SECTION_POST_DATA)
		return;

	/* Quick exit if no dependencies at all */
	if (te->nDeps == 0)
		return;

	/*
	 * Most POST_DATA items are ALTER TABLEs or some moral equivalent of that,
	 * and hence require exclusive lock.  However, we know that CREATE INDEX
	 * does not.  (Maybe someday index-creating CONSTRAINTs will fall in that
	 * category too ... but today is not that day.)
	 */
	if (strcmp(te->desc, "INDEX") == 0)
		return;

	/*
	 * We assume the entry requires exclusive lock on each TABLE or TABLE DATA
	 * item listed among its dependencies.  Originally all of these would have
	 * been TABLE items, but repoint_table_dependencies would have repointed
	 * them to the TABLE DATA items if those are present (which they might not
	 * be, eg in a schema-only dump).  Note that all of the entries we are
	 * processing here are POST_DATA; otherwise there might be a significant
	 * difference between a dependency on a table and a dependency on its
	 * data, so that closer analysis would be needed here.
	 */
	lockids = (DumpId *) pg_malloc(te->nDeps * sizeof(DumpId));
	nlockids = 0;
	for (i = 0; i < te->nDeps; i++)
	{
		DumpId		depid = te->dependencies[i];

		if (depid <= AH->maxDumpId && AH->tocsByDumpId[depid] != NULL &&
			((strcmp(AH->tocsByDumpId[depid]->desc, "TABLE DATA") == 0) ||
			 strcmp(AH->tocsByDumpId[depid]->desc, "TABLE") == 0))
			lockids[nlockids++] = depid;
	}

	if (nlockids == 0)
	{
		free(lockids);
		return;
	}

	te->lockDeps = pg_realloc(lockids, nlockids * sizeof(DumpId));
	te->nLockDeps = nlockids;
}