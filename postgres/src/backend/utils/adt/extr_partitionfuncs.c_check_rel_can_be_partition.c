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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 char RELKIND_PARTITIONED_INDEX ; 
 char RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  SearchSysCacheExists1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_rel_relispartition (int /*<<< orphan*/ ) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
check_rel_can_be_partition(Oid relid)
{
	char		relkind;
	bool		relispartition;

	/* Check if relation exists */
	if (!SearchSysCacheExists1(RELOID, ObjectIdGetDatum(relid)))
		return false;

	relkind = get_rel_relkind(relid);
	relispartition = get_rel_relispartition(relid);

	/* Only allow relation types that can appear in partition trees. */
	if (!relispartition &&
		relkind != RELKIND_PARTITIONED_TABLE &&
		relkind != RELKIND_PARTITIONED_INDEX)
		return false;

	return true;
}