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
typedef  int /*<<< orphan*/  A_Expr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  lexpr ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  rexpr ; 

__attribute__((used)) static bool
_equalAExpr(const A_Expr *a, const A_Expr *b)
{
	COMPARE_SCALAR_FIELD(kind);
	COMPARE_NODE_FIELD(name);
	COMPARE_NODE_FIELD(lexpr);
	COMPARE_NODE_FIELD(rexpr);
	COMPARE_LOCATION_FIELD(location);

	return true;
}