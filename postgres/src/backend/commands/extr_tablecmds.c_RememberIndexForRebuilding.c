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
struct TYPE_4__ {int /*<<< orphan*/  changedIndexDefs; int /*<<< orphan*/  changedIndexOids; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ AlteredTableInfo ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RememberConstraintForRebuilding (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  get_index_constraint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lappend_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pg_get_indexdef_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RememberIndexForRebuilding(Oid indoid, AlteredTableInfo *tab)
{
	/*
	 * This de-duplication check is critical for two independent reasons: we
	 * mustn't try to recreate the same index twice, and if an index depends
	 * on more than one column whose type is to be altered, we must capture
	 * its definition string before applying any of the column type changes.
	 * ruleutils.c will get confused if we ask again later.
	 */
	if (!list_member_oid(tab->changedIndexOids, indoid))
	{
		/*
		 * Before adding it as an index-to-rebuild, we'd better see if it
		 * belongs to a constraint, and if so rebuild the constraint instead.
		 * Typically this check fails, because constraint indexes normally
		 * have only dependencies on their constraint.  But it's possible for
		 * such an index to also have direct dependencies on table columns,
		 * for example with a partial exclusion constraint.
		 */
		Oid			conoid = get_index_constraint(indoid);

		if (OidIsValid(conoid))
		{
			RememberConstraintForRebuilding(conoid, tab);
		}
		else
		{
			/* OK, capture the index's existing definition string */
			char	   *defstring = pg_get_indexdef_string(indoid);

			tab->changedIndexOids = lappend_oid(tab->changedIndexOids,
												indoid);
			tab->changedIndexDefs = lappend(tab->changedIndexDefs,
											defstring);
		}
	}
}