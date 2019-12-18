#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int tdrefcount; } ;
struct TYPE_9__ {int /*<<< orphan*/  relnatts; } ;
struct TYPE_8__ {TYPE_5__* rd_att; TYPE_2__* rd_rel; int /*<<< orphan*/ * rd_smgr; } ;
typedef  int /*<<< orphan*/  RelationData ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_TUPLE_SIZE ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 TYPE_5__* CreateTemplateTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static Relation
AllocateRelationDesc(Form_pg_class relp)
{
	Relation	relation;
	MemoryContext oldcxt;
	Form_pg_class relationForm;

	/* Relcache entries must live in CacheMemoryContext */
	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

	/*
	 * allocate and zero space for new relation descriptor
	 */
	relation = (Relation) palloc0(sizeof(RelationData));

	/* make sure relation is marked as having no open file yet */
	relation->rd_smgr = NULL;

	/*
	 * Copy the relation tuple form
	 *
	 * We only allocate space for the fixed fields, ie, CLASS_TUPLE_SIZE. The
	 * variable-length fields (relacl, reloptions) are NOT stored in the
	 * relcache --- there'd be little point in it, since we don't copy the
	 * tuple's nulls bitmap and hence wouldn't know if the values are valid.
	 * Bottom line is that relacl *cannot* be retrieved from the relcache. Get
	 * it from the syscache if you need it.  The same goes for the original
	 * form of reloptions (however, we do store the parsed form of reloptions
	 * in rd_options).
	 */
	relationForm = (Form_pg_class) palloc(CLASS_TUPLE_SIZE);

	memcpy(relationForm, relp, CLASS_TUPLE_SIZE);

	/* initialize relation tuple form */
	relation->rd_rel = relationForm;

	/* and allocate attribute tuple form storage */
	relation->rd_att = CreateTemplateTupleDesc(relationForm->relnatts);
	/* which we mark as a reference-counted tupdesc */
	relation->rd_att->tdrefcount = 1;

	MemoryContextSwitchTo(oldcxt);

	return relation;
}