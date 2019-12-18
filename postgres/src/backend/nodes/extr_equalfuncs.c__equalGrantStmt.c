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
typedef  int /*<<< orphan*/  GrantStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  behavior ; 
 int /*<<< orphan*/  grant_option ; 
 int /*<<< orphan*/  grantees ; 
 int /*<<< orphan*/  is_grant ; 
 int /*<<< orphan*/  objects ; 
 int /*<<< orphan*/  objtype ; 
 int /*<<< orphan*/  privileges ; 
 int /*<<< orphan*/  targtype ; 

__attribute__((used)) static bool
_equalGrantStmt(const GrantStmt *a, const GrantStmt *b)
{
	COMPARE_SCALAR_FIELD(is_grant);
	COMPARE_SCALAR_FIELD(targtype);
	COMPARE_SCALAR_FIELD(objtype);
	COMPARE_NODE_FIELD(objects);
	COMPARE_NODE_FIELD(privileges);
	COMPARE_NODE_FIELD(grantees);
	COMPARE_SCALAR_FIELD(grant_option);
	COMPARE_SCALAR_FIELD(behavior);

	return true;
}