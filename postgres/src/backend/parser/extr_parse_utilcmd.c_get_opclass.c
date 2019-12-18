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
struct TYPE_2__ {int /*<<< orphan*/  opcname; int /*<<< orphan*/  opcnamespace; int /*<<< orphan*/  opcmethod; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_opclass ;

/* Variables and functions */
 int /*<<< orphan*/  CLAOID ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDefaultOpClass (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
get_opclass(Oid opclass, Oid actual_datatype)
{
	List	   *result = NIL;
	HeapTuple	ht_opc;
	Form_pg_opclass opc_rec;

	ht_opc = SearchSysCache1(CLAOID, ObjectIdGetDatum(opclass));
	if (!HeapTupleIsValid(ht_opc))
		elog(ERROR, "cache lookup failed for opclass %u", opclass);
	opc_rec = (Form_pg_opclass) GETSTRUCT(ht_opc);

	if (GetDefaultOpClass(actual_datatype, opc_rec->opcmethod) != opclass)
	{
		/* For simplicity, we always schema-qualify the name */
		char	   *nsp_name = get_namespace_name(opc_rec->opcnamespace);
		char	   *opc_name = pstrdup(NameStr(opc_rec->opcname));

		result = list_make2(makeString(nsp_name), makeString(opc_name));
	}

	ReleaseSysCache(ht_opc);
	return result;
}