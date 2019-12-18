#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rte ;
struct TYPE_18__ {TYPE_3__* addrs; TYPE_2__* rtables; } ;
typedef  TYPE_1__ find_expr_references_context ;
struct TYPE_21__ {scalar_t__ classId; scalar_t__ objectId; } ;
struct TYPE_20__ {scalar_t__ numrefs; TYPE_4__* refs; } ;
struct TYPE_19__ {int /*<<< orphan*/  rellockmode; int /*<<< orphan*/  relkind; scalar_t__ relid; int /*<<< orphan*/  rtekind; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__ ObjectAddresses ;
typedef  TYPE_4__ ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  DependencyType ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RELKIND_RELATION ; 
 int /*<<< orphan*/  RTE_RELATION ; 
 scalar_t__ RelationRelationId ; 
 int /*<<< orphan*/  T_RangeTblEntry ; 
 int /*<<< orphan*/  add_exact_object_address (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  eliminate_duplicate_dependencies (TYPE_3__*) ; 
 int /*<<< orphan*/  find_expr_references_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free_object_addresses (TYPE_3__*) ; 
 TYPE_2__* list_make1 (TYPE_2__*) ; 
 void* new_object_addresses () ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_4__*,TYPE_4__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordMultipleDependencies (TYPE_4__ const*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 

void
recordDependencyOnSingleRelExpr(const ObjectAddress *depender,
								Node *expr, Oid relId,
								DependencyType behavior,
								DependencyType self_behavior,
								bool reverse_self)
{
	find_expr_references_context context;
	RangeTblEntry rte;

	context.addrs = new_object_addresses();

	/* We gin up a rather bogus rangetable list to handle Vars */
	MemSet(&rte, 0, sizeof(rte));
	rte.type = T_RangeTblEntry;
	rte.rtekind = RTE_RELATION;
	rte.relid = relId;
	rte.relkind = RELKIND_RELATION; /* no need for exactness here */
	rte.rellockmode = AccessShareLock;

	context.rtables = list_make1(list_make1(&rte));

	/* Scan the expression tree for referenceable objects */
	find_expr_references_walker(expr, &context);

	/* Remove any duplicates */
	eliminate_duplicate_dependencies(context.addrs);

	/* Separate self-dependencies if necessary */
	if ((behavior != self_behavior || reverse_self) &&
		context.addrs->numrefs > 0)
	{
		ObjectAddresses *self_addrs;
		ObjectAddress *outobj;
		int			oldref,
					outrefs;

		self_addrs = new_object_addresses();

		outobj = context.addrs->refs;
		outrefs = 0;
		for (oldref = 0; oldref < context.addrs->numrefs; oldref++)
		{
			ObjectAddress *thisobj = context.addrs->refs + oldref;

			if (thisobj->classId == RelationRelationId &&
				thisobj->objectId == relId)
			{
				/* Move this ref into self_addrs */
				add_exact_object_address(thisobj, self_addrs);
			}
			else
			{
				/* Keep it in context.addrs */
				*outobj = *thisobj;
				outobj++;
				outrefs++;
			}
		}
		context.addrs->numrefs = outrefs;

		/* Record the self-dependencies with the appropriate direction */
		if (!reverse_self)
			recordMultipleDependencies(depender,
									   self_addrs->refs, self_addrs->numrefs,
									   self_behavior);
		else
		{
			/* Can't use recordMultipleDependencies, so do it the hard way */
			int			selfref;

			for (selfref = 0; selfref < self_addrs->numrefs; selfref++)
			{
				ObjectAddress *thisobj = self_addrs->refs + selfref;

				recordDependencyOn(thisobj, depender, self_behavior);
			}
		}

		free_object_addresses(self_addrs);
	}

	/* Record the external dependencies */
	recordMultipleDependencies(depender,
							   context.addrs->refs, context.addrs->numrefs,
							   behavior);

	free_object_addresses(context.addrs);
}