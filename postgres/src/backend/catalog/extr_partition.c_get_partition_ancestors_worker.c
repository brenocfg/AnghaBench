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
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 scalar_t__ get_partition_parent_worker (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
get_partition_ancestors_worker(Relation inhRel, Oid relid, List **ancestors)
{
	Oid			parentOid;

	/* Recursion ends at the topmost level, ie., when there's no parent */
	parentOid = get_partition_parent_worker(inhRel, relid);
	if (parentOid == InvalidOid)
		return;

	*ancestors = lappend_oid(*ancestors, parentOid);
	get_partition_ancestors_worker(inhRel, parentOid, ancestors);
}