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
typedef  int /*<<< orphan*/  CoalesceExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  coalescecollid ; 
 int /*<<< orphan*/  coalescetype ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static bool
_equalCoalesceExpr(const CoalesceExpr *a, const CoalesceExpr *b)
{
	COMPARE_SCALAR_FIELD(coalescetype);
	COMPARE_SCALAR_FIELD(coalescecollid);
	COMPARE_NODE_FIELD(args);
	COMPARE_LOCATION_FIELD(location);

	return true;
}