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
typedef  int /*<<< orphan*/  PLpgSQL_type ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_TABLE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelnameGetRelid (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  get_rel_type_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeTypeName (char*) ; 
 int /*<<< orphan*/ * plpgsql_build_datatype (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PLpgSQL_type *
plpgsql_parse_wordrowtype(char *ident)
{
	Oid			classOid;

	/*
	 * Look up the relation.  Note that because relation rowtypes have the
	 * same names as their relations, this could be handled as a type lookup
	 * equally well; we use the relation lookup code path only because the
	 * errors thrown here have traditionally referred to relations not types.
	 * But we'll make a TypeName in case we have to do re-look-up of the type.
	 */
	classOid = RelnameGetRelid(ident);
	if (!OidIsValid(classOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_TABLE),
				 errmsg("relation \"%s\" does not exist", ident)));

	/* Build and return the row type struct */
	return plpgsql_build_datatype(get_rel_type_id(classOid), -1, InvalidOid,
								  makeTypeName(ident));
}