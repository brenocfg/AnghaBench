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
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
#define  BMS_EMPTY_SET 130 
#define  BMS_MULTIPLE 129 
#define  BMS_SINGLETON 128 
 int /*<<< orphan*/  ERROR ; 
 int bms_membership (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_singleton_member (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * find_base_rel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_join_rel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RelOptInfo *
find_join_input_rel(PlannerInfo *root, Relids relids)
{
	RelOptInfo *rel = NULL;

	switch (bms_membership(relids))
	{
		case BMS_EMPTY_SET:
			/* should not happen */
			break;
		case BMS_SINGLETON:
			rel = find_base_rel(root, bms_singleton_member(relids));
			break;
		case BMS_MULTIPLE:
			rel = find_join_rel(root, relids);
			break;
	}

	if (rel == NULL)
		elog(ERROR, "could not find RelOptInfo for given relids");

	return rel;
}