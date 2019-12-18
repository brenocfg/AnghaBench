#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/ * amoptions_function ;
struct TYPE_7__ {int /*<<< orphan*/ * rd_options; TYPE_2__* rd_indam; TYPE_1__* rd_rel; } ;
struct TYPE_6__ {int /*<<< orphan*/ * amoptions; } ;
struct TYPE_5__ {int relkind; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  GetPgClassDescriptor () ; 
 int /*<<< orphan*/ * MemoryContextAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RELKIND_INDEX 134 
#define  RELKIND_MATVIEW 133 
#define  RELKIND_PARTITIONED_INDEX 132 
#define  RELKIND_PARTITIONED_TABLE 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_TOASTVALUE 129 
#define  RELKIND_VIEW 128 
 int /*<<< orphan*/  VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extractRelOptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
RelationParseRelOptions(Relation relation, HeapTuple tuple)
{
	bytea	   *options;
	amoptions_function amoptsfn;

	relation->rd_options = NULL;

	/*
	 * Look up any AM-specific parse function; fall out if relkind should not
	 * have options.
	 */
	switch (relation->rd_rel->relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_TOASTVALUE:
		case RELKIND_VIEW:
		case RELKIND_MATVIEW:
		case RELKIND_PARTITIONED_TABLE:
			amoptsfn = NULL;
			break;
		case RELKIND_INDEX:
		case RELKIND_PARTITIONED_INDEX:
			amoptsfn = relation->rd_indam->amoptions;
			break;
		default:
			return;
	}

	/*
	 * Fetch reloptions from tuple; have to use a hardwired descriptor because
	 * we might not have any other for pg_class yet (consider executing this
	 * code for pg_class itself)
	 */
	options = extractRelOptions(tuple, GetPgClassDescriptor(), amoptsfn);

	/*
	 * Copy parsed data into CacheMemoryContext.  To guard against the
	 * possibility of leaks in the reloptions code, we want to do the actual
	 * parsing in the caller's memory context and copy the results into
	 * CacheMemoryContext after the fact.
	 */
	if (options)
	{
		relation->rd_options = MemoryContextAlloc(CacheMemoryContext,
												  VARSIZE(options));
		memcpy(relation->rd_options, options, VARSIZE(options));
		pfree(options);
	}
}