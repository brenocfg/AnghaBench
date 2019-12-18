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
struct TYPE_4__ {int /*<<< orphan*/ * rd_indcollation; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASHSTANDARD_PROC ; 
 int /*<<< orphan*/ * index_getprocinfo (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

uint32
_hash_datum2hashkey(Relation rel, Datum key)
{
	FmgrInfo   *procinfo;
	Oid			collation;

	/* XXX assumes index has only one attribute */
	procinfo = index_getprocinfo(rel, 1, HASHSTANDARD_PROC);
	collation = rel->rd_indcollation[0];

	return DatumGetUInt32(FunctionCall1Coll(procinfo, collation, key));
}