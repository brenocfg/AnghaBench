#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct policydb {scalar_t__ policyvers; TYPE_3__ p_types; TYPE_2__ p_roles; TYPE_1__ p_users; } ;

/* Variables and functions */
 scalar_t__ POLICYDB_VERSION_BOUNDARY ; 
 int hashtab_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct policydb*) ; 
 int /*<<< orphan*/  role_bounds_sanity_check ; 
 int /*<<< orphan*/  type_bounds_sanity_check ; 
 int /*<<< orphan*/  user_bounds_sanity_check ; 

__attribute__((used)) static int policydb_bounds_sanity_check(struct policydb *p)
{
	int rc;

	if (p->policyvers < POLICYDB_VERSION_BOUNDARY)
		return 0;

	rc = hashtab_map(p->p_users.table,
			 user_bounds_sanity_check, p);
	if (rc)
		return rc;

	rc = hashtab_map(p->p_roles.table,
			 role_bounds_sanity_check, p);
	if (rc)
		return rc;

	rc = hashtab_map(p->p_types.table,
			 type_bounds_sanity_check, p);
	if (rc)
		return rc;

	return 0;
}