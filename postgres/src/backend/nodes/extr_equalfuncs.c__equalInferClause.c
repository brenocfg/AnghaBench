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
typedef  int /*<<< orphan*/  InferClause ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conname ; 
 int /*<<< orphan*/  indexElems ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  whereClause ; 

__attribute__((used)) static bool
_equalInferClause(const InferClause *a, const InferClause *b)
{
	COMPARE_NODE_FIELD(indexElems);
	COMPARE_NODE_FIELD(whereClause);
	COMPARE_STRING_FIELD(conname);
	COMPARE_LOCATION_FIELD(location);

	return true;
}