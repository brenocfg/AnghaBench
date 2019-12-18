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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2OID ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 char* get_attname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quote_identifier (char*) ; 

__attribute__((used)) static int
decompile_column_index_array(Datum column_index_array, Oid relId,
							 StringInfo buf)
{
	Datum	   *keys;
	int			nKeys;
	int			j;

	/* Extract data from array of int16 */
	deconstruct_array(DatumGetArrayTypeP(column_index_array),
					  INT2OID, 2, true, 's',
					  &keys, NULL, &nKeys);

	for (j = 0; j < nKeys; j++)
	{
		char	   *colName;

		colName = get_attname(relId, DatumGetInt16(keys[j]), false);

		if (j == 0)
			appendStringInfoString(buf, quote_identifier(colName));
		else
			appendStringInfo(buf, ", %s", quote_identifier(colName));
	}

	return nKeys;
}