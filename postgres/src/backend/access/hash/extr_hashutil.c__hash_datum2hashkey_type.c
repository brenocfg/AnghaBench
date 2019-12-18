#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int /*<<< orphan*/ * rd_indcollation; int /*<<< orphan*/ * rd_opfamily; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASHSTANDARD_PROC ; 
 int /*<<< orphan*/  OidFunctionCall1Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegProcedureIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opfamily_proc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32
_hash_datum2hashkey_type(Relation rel, Datum key, Oid keytype)
{
	RegProcedure hash_proc;
	Oid			collation;

	/* XXX assumes index has only one attribute */
	hash_proc = get_opfamily_proc(rel->rd_opfamily[0],
								  keytype,
								  keytype,
								  HASHSTANDARD_PROC);
	if (!RegProcedureIsValid(hash_proc))
		elog(ERROR, "missing support function %d(%u,%u) for index \"%s\"",
			 HASHSTANDARD_PROC, keytype, keytype,
			 RelationGetRelationName(rel));
	collation = rel->rd_indcollation[0];

	return DatumGetUInt32(OidFunctionCall1Coll(hash_proc, collation, key));
}