#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  amoptions_function ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_2__ {int relkind; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_class_reloptions ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
#define  RELKIND_FOREIGN_TABLE 135 
#define  RELKIND_INDEX 134 
#define  RELKIND_MATVIEW 133 
#define  RELKIND_PARTITIONED_INDEX 132 
#define  RELKIND_PARTITIONED_TABLE 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_TOASTVALUE 129 
#define  RELKIND_VIEW 128 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * heap_reloptions (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * index_reloptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * partitioned_table_reloptions (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * view_reloptions (int /*<<< orphan*/ ,int) ; 

bytea *
extractRelOptions(HeapTuple tuple, TupleDesc tupdesc,
				  amoptions_function amoptions)
{
	bytea	   *options;
	bool		isnull;
	Datum		datum;
	Form_pg_class classForm;

	datum = fastgetattr(tuple,
						Anum_pg_class_reloptions,
						tupdesc,
						&isnull);
	if (isnull)
		return NULL;

	classForm = (Form_pg_class) GETSTRUCT(tuple);

	/* Parse into appropriate format; don't error out here */
	switch (classForm->relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_TOASTVALUE:
		case RELKIND_MATVIEW:
			options = heap_reloptions(classForm->relkind, datum, false);
			break;
		case RELKIND_PARTITIONED_TABLE:
			options = partitioned_table_reloptions(datum, false);
			break;
		case RELKIND_VIEW:
			options = view_reloptions(datum, false);
			break;
		case RELKIND_INDEX:
		case RELKIND_PARTITIONED_INDEX:
			options = index_reloptions(amoptions, datum, false);
			break;
		case RELKIND_FOREIGN_TABLE:
			options = NULL;
			break;
		default:
			Assert(false);		/* can't get here */
			options = NULL;		/* keep compiler quiet */
			break;
	}

	return options;
}