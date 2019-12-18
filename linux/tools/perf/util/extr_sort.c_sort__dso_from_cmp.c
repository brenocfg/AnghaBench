#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hist_entry {TYPE_2__* branch_info; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;
struct TYPE_5__ {TYPE_1__ from; } ;

/* Variables and functions */
 int /*<<< orphan*/  _sort__dso_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_null (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int64_t
sort__dso_from_cmp(struct hist_entry *left, struct hist_entry *right)
{
	if (!left->branch_info || !right->branch_info)
		return cmp_null(left->branch_info, right->branch_info);

	return _sort__dso_cmp(left->branch_info->from.map,
			      right->branch_info->from.map);
}