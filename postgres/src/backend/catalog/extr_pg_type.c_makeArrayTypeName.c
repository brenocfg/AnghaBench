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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheExists2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_identifier (char*,int,int) ; 

char *
makeArrayTypeName(const char *typeName, Oid typeNamespace)
{
	char	   *arr = (char *) palloc(NAMEDATALEN);
	int			namelen = strlen(typeName);
	Relation	pg_type_desc;
	int			i;

	/*
	 * The idea is to prepend underscores as needed until we make a name that
	 * doesn't collide with anything...
	 */
	pg_type_desc = table_open(TypeRelationId, AccessShareLock);

	for (i = 1; i < NAMEDATALEN - 1; i++)
	{
		arr[i - 1] = '_';
		if (i + namelen < NAMEDATALEN)
			strcpy(arr + i, typeName);
		else
		{
			memcpy(arr + i, typeName, NAMEDATALEN - i);
			truncate_identifier(arr, NAMEDATALEN, false);
		}
		if (!SearchSysCacheExists2(TYPENAMENSP,
								   CStringGetDatum(arr),
								   ObjectIdGetDatum(typeNamespace)))
			break;
	}

	table_close(pg_type_desc, AccessShareLock);

	if (i >= NAMEDATALEN - 1)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("could not form array type name for type \"%s\"",
						typeName)));

	return arr;
}