#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_9__ {int /*<<< orphan*/  fn_input_collation; } ;
struct TYPE_8__ {scalar_t__ typrelid; int /*<<< orphan*/  typisdefined; } ;
struct TYPE_7__ {int itemtype; size_t itemno; } ;
struct TYPE_6__ {int /*<<< orphan*/ * datatype; } ;
typedef  TYPE_1__ PLpgSQL_var ;
typedef  int /*<<< orphan*/  PLpgSQL_type ;
typedef  TYPE_2__ PLpgSQL_nsitem ;
typedef  scalar_t__ HeapTuple ;
typedef  TYPE_3__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (scalar_t__) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ LookupTypeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
#define  PLPGSQL_NSTYPE_VAR 128 
 int /*<<< orphan*/  ReleaseSysCache (scalar_t__) ; 
 int /*<<< orphan*/ * build_datatype (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeTypeName (char*) ; 
 scalar_t__* plpgsql_Datums ; 
 TYPE_5__* plpgsql_curr_compile ; 
 TYPE_2__* plpgsql_ns_lookup (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_ns_top () ; 

PLpgSQL_type *
plpgsql_parse_wordtype(char *ident)
{
	PLpgSQL_type *dtype;
	PLpgSQL_nsitem *nse;
	TypeName   *typeName;
	HeapTuple	typeTup;

	/*
	 * Do a lookup in the current namespace stack
	 */
	nse = plpgsql_ns_lookup(plpgsql_ns_top(), false,
							ident, NULL, NULL,
							NULL);

	if (nse != NULL)
	{
		switch (nse->itemtype)
		{
			case PLPGSQL_NSTYPE_VAR:
				return ((PLpgSQL_var *) (plpgsql_Datums[nse->itemno]))->datatype;

				/* XXX perhaps allow REC/ROW here? */

			default:
				return NULL;
		}
	}

	/*
	 * Word wasn't found in the namespace stack. Try to find a data type with
	 * that name, but ignore shell types and complex types.
	 */
	typeName = makeTypeName(ident);
	typeTup = LookupTypeName(NULL, typeName, NULL, false);
	if (typeTup)
	{
		Form_pg_type typeStruct = (Form_pg_type) GETSTRUCT(typeTup);

		if (!typeStruct->typisdefined ||
			typeStruct->typrelid != InvalidOid)
		{
			ReleaseSysCache(typeTup);
			return NULL;
		}

		dtype = build_datatype(typeTup, -1,
							   plpgsql_curr_compile->fn_input_collation,
							   typeName);

		ReleaseSysCache(typeTup);
		return dtype;
	}

	/*
	 * Nothing found - up to now it's a word without any special meaning for
	 * us.
	 */
	return NULL;
}