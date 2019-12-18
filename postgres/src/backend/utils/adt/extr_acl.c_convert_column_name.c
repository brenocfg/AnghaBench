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
typedef  int /*<<< orphan*/  text ;
struct TYPE_2__ {int /*<<< orphan*/  attnum; scalar_t__ attisdropped; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNAME ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidAttrNumber ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static AttrNumber
convert_column_name(Oid tableoid, text *column)
{
	char	   *colname;
	HeapTuple	attTuple;
	AttrNumber	attnum;

	colname = text_to_cstring(column);

	/*
	 * We don't use get_attnum() here because it will report that dropped
	 * columns don't exist.  We need to treat dropped columns differently from
	 * nonexistent columns.
	 */
	attTuple = SearchSysCache2(ATTNAME,
							   ObjectIdGetDatum(tableoid),
							   CStringGetDatum(colname));
	if (HeapTupleIsValid(attTuple))
	{
		Form_pg_attribute attributeForm;

		attributeForm = (Form_pg_attribute) GETSTRUCT(attTuple);
		/* We want to return NULL for dropped columns */
		if (attributeForm->attisdropped)
			attnum = InvalidAttrNumber;
		else
			attnum = attributeForm->attnum;
		ReleaseSysCache(attTuple);
	}
	else
	{
		char	   *tablename = get_rel_name(tableoid);

		/*
		 * If the table OID is bogus, or it's just been dropped, we'll get
		 * NULL back.  In such cases we want has_column_privilege to return
		 * NULL too, so just return InvalidAttrNumber.
		 */
		if (tablename != NULL)
		{
			/* tableoid exists, colname does not, so throw error */
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_COLUMN),
					 errmsg("column \"%s\" of relation \"%s\" does not exist",
							colname, tablename)));
		}
		/* tableoid doesn't exist, so act like attisdropped case */
		attnum = InvalidAttrNumber;
	}

	pfree(colname);
	return attnum;
}