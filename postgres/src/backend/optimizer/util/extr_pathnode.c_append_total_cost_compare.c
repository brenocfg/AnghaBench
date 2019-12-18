#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  relids; } ;
typedef  TYPE_2__ Path ;
typedef  int /*<<< orphan*/  ListCell ;

/* Variables and functions */
 int /*<<< orphan*/  TOTAL_COST ; 
 int bms_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int compare_path_costs (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lfirst (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
append_total_cost_compare(const ListCell *a, const ListCell *b)
{
	Path	   *path1 = (Path *) lfirst(a);
	Path	   *path2 = (Path *) lfirst(b);
	int			cmp;

	cmp = compare_path_costs(path1, path2, TOTAL_COST);
	if (cmp != 0)
		return -cmp;
	return bms_compare(path1->parent->relids, path2->parent->relids);
}