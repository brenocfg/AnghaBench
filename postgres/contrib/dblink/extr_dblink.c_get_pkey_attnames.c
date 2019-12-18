#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {int /*<<< orphan*/ * values; } ;
struct TYPE_11__ {int indnkeyatts; TYPE_1__ indkey; scalar_t__ indisprimary; } ;
struct TYPE_10__ {int /*<<< orphan*/  rd_att; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_index_indrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexIndrelidIndexId ; 
 int /*<<< orphan*/  IndexRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 char* SPI_fname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char **
get_pkey_attnames(Relation rel, int16 *indnkeyatts)
{
	Relation	indexRelation;
	ScanKeyData skey;
	SysScanDesc scan;
	HeapTuple	indexTuple;
	int			i;
	char	  **result = NULL;
	TupleDesc	tupdesc;

	/* initialize indnkeyatts to 0 in case no primary key exists */
	*indnkeyatts = 0;

	tupdesc = rel->rd_att;

	/* Prepare to scan pg_index for entries having indrelid = this rel. */
	indexRelation = table_open(IndexRelationId, AccessShareLock);
	ScanKeyInit(&skey,
				Anum_pg_index_indrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(rel)));

	scan = systable_beginscan(indexRelation, IndexIndrelidIndexId, true,
							  NULL, 1, &skey);

	while (HeapTupleIsValid(indexTuple = systable_getnext(scan)))
	{
		Form_pg_index index = (Form_pg_index) GETSTRUCT(indexTuple);

		/* we're only interested if it is the primary key */
		if (index->indisprimary)
		{
			*indnkeyatts = index->indnkeyatts;
			if (*indnkeyatts > 0)
			{
				result = (char **) palloc(*indnkeyatts * sizeof(char *));

				for (i = 0; i < *indnkeyatts; i++)
					result[i] = SPI_fname(tupdesc, index->indkey.values[i]);
			}
			break;
		}
	}

	systable_endscan(scan);
	table_close(indexRelation, AccessShareLock);

	return result;
}