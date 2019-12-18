#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ tdrefcount; } ;
struct TYPE_10__ {scalar_t__ rd_partcheckcxt; scalar_t__ rd_pdcxt; scalar_t__ rd_partkeycxt; TYPE_1__* rd_rsdesc; scalar_t__ rd_rulescxt; scalar_t__ rd_indexcxt; struct TYPE_10__* rd_fdwroutine; struct TYPE_10__* rd_amcache; struct TYPE_10__* rd_indextuple; struct TYPE_10__* rd_options; struct TYPE_10__* rd_pubactions; int /*<<< orphan*/  rd_idattr; int /*<<< orphan*/  rd_pkattr; int /*<<< orphan*/  rd_keyattr; int /*<<< orphan*/  rd_indexattr; int /*<<< orphan*/  rd_indexlist; int /*<<< orphan*/  rd_fkeylist; int /*<<< orphan*/  trigdesc; TYPE_4__* rd_att; struct TYPE_10__* rd_rel; } ;
struct TYPE_9__ {scalar_t__ rscxt; } ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FreeTriggerDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeTupleDesc (TYPE_4__*) ; 
 int /*<<< orphan*/  MemoryContextDelete (scalar_t__) ; 
 int /*<<< orphan*/  RelationCloseSmgr (TYPE_2__*) ; 
 int RelationHasReferenceCountZero (TYPE_2__*) ; 
 int /*<<< orphan*/  RememberToFreeTupleDescAtEOX (TYPE_4__*) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free_deep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
RelationDestroyRelation(Relation relation, bool remember_tupdesc)
{
	Assert(RelationHasReferenceCountZero(relation));

	/*
	 * Make sure smgr and lower levels close the relation's files, if they
	 * weren't closed already.  (This was probably done by caller, but let's
	 * just be real sure.)
	 */
	RelationCloseSmgr(relation);

	/*
	 * Free all the subsidiary data structures of the relcache entry, then the
	 * entry itself.
	 */
	if (relation->rd_rel)
		pfree(relation->rd_rel);
	/* can't use DecrTupleDescRefCount here */
	Assert(relation->rd_att->tdrefcount > 0);
	if (--relation->rd_att->tdrefcount == 0)
	{
		/*
		 * If we Rebuilt a relcache entry during a transaction then its
		 * possible we did that because the TupDesc changed as the result of
		 * an ALTER TABLE that ran at less than AccessExclusiveLock. It's
		 * possible someone copied that TupDesc, in which case the copy would
		 * point to free'd memory. So if we rebuild an entry we keep the
		 * TupDesc around until end of transaction, to be safe.
		 */
		if (remember_tupdesc)
			RememberToFreeTupleDescAtEOX(relation->rd_att);
		else
			FreeTupleDesc(relation->rd_att);
	}
	FreeTriggerDesc(relation->trigdesc);
	list_free_deep(relation->rd_fkeylist);
	list_free(relation->rd_indexlist);
	bms_free(relation->rd_indexattr);
	bms_free(relation->rd_keyattr);
	bms_free(relation->rd_pkattr);
	bms_free(relation->rd_idattr);
	if (relation->rd_pubactions)
		pfree(relation->rd_pubactions);
	if (relation->rd_options)
		pfree(relation->rd_options);
	if (relation->rd_indextuple)
		pfree(relation->rd_indextuple);
	if (relation->rd_amcache)
		pfree(relation->rd_amcache);
	if (relation->rd_fdwroutine)
		pfree(relation->rd_fdwroutine);
	if (relation->rd_indexcxt)
		MemoryContextDelete(relation->rd_indexcxt);
	if (relation->rd_rulescxt)
		MemoryContextDelete(relation->rd_rulescxt);
	if (relation->rd_rsdesc)
		MemoryContextDelete(relation->rd_rsdesc->rscxt);
	if (relation->rd_partkeycxt)
		MemoryContextDelete(relation->rd_partkeycxt);
	if (relation->rd_pdcxt)
		MemoryContextDelete(relation->rd_pdcxt);
	if (relation->rd_partcheckcxt)
		MemoryContextDelete(relation->rd_partcheckcxt);
	pfree(relation);
}