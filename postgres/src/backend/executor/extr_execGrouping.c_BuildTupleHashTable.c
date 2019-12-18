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
typedef  int /*<<< orphan*/  TupleHashTable ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTupleHashTableExt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

TupleHashTable
BuildTupleHashTable(PlanState *parent,
					TupleDesc inputDesc,
					int numCols, AttrNumber *keyColIdx,
					const Oid *eqfuncoids,
					FmgrInfo *hashfunctions,
					Oid *collations,
					long nbuckets, Size additionalsize,
					MemoryContext tablecxt,
					MemoryContext tempcxt,
					bool use_variable_hash_iv)
{
	return BuildTupleHashTableExt(parent,
								  inputDesc,
								  numCols, keyColIdx,
								  eqfuncoids,
								  hashfunctions,
								  collations,
								  nbuckets, additionalsize,
								  tablecxt,
								  tablecxt,
								  tempcxt,
								  use_variable_hash_iv);
}