#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  changedConstraintDefs; int /*<<< orphan*/  changedConstraintOids; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ AlteredTableInfo ;

/* Variables and functions */
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lappend_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pg_get_constraintdef_command (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RememberConstraintForRebuilding(Oid conoid, AlteredTableInfo *tab)
{
	/*
	 * This de-duplication check is critical for two independent reasons: we
	 * mustn't try to recreate the same constraint twice, and if a constraint
	 * depends on more than one column whose type is to be altered, we must
	 * capture its definition string before applying any of the column type
	 * changes.  ruleutils.c will get confused if we ask again later.
	 */
	if (!list_member_oid(tab->changedConstraintOids, conoid))
	{
		/* OK, capture the constraint's existing definition string */
		char	   *defstring = pg_get_constraintdef_command(conoid);

		tab->changedConstraintOids = lappend_oid(tab->changedConstraintOids,
												 conoid);
		tab->changedConstraintDefs = lappend(tab->changedConstraintDefs,
											 defstring);
	}
}