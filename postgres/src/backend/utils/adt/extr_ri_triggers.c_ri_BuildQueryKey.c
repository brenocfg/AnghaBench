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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {int /*<<< orphan*/  constraint_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  constr_queryno; int /*<<< orphan*/  constr_id; } ;
typedef  TYPE_1__ RI_QueryKey ;
typedef  TYPE_2__ RI_ConstraintInfo ;

/* Variables and functions */

__attribute__((used)) static void
ri_BuildQueryKey(RI_QueryKey *key, const RI_ConstraintInfo *riinfo,
				 int32 constr_queryno)
{
	/*
	 * We assume struct RI_QueryKey contains no padding bytes, else we'd need
	 * to use memset to clear them.
	 */
	key->constr_id = riinfo->constraint_id;
	key->constr_queryno = constr_queryno;
}