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
typedef  int /*<<< orphan*/  WindowDef ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endOffset ; 
 int /*<<< orphan*/  frameOptions ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  orderClause ; 
 int /*<<< orphan*/  partitionClause ; 
 int /*<<< orphan*/  refname ; 
 int /*<<< orphan*/  startOffset ; 

__attribute__((used)) static bool
_equalWindowDef(const WindowDef *a, const WindowDef *b)
{
	COMPARE_STRING_FIELD(name);
	COMPARE_STRING_FIELD(refname);
	COMPARE_NODE_FIELD(partitionClause);
	COMPARE_NODE_FIELD(orderClause);
	COMPARE_SCALAR_FIELD(frameOptions);
	COMPARE_NODE_FIELD(startOffset);
	COMPARE_NODE_FIELD(endOffset);
	COMPARE_LOCATION_FIELD(location);

	return true;
}