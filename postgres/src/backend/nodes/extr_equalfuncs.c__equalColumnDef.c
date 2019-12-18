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
typedef  int /*<<< orphan*/  ColumnDef ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collClause ; 
 int /*<<< orphan*/  collOid ; 
 int /*<<< orphan*/  colname ; 
 int /*<<< orphan*/  constraints ; 
 int /*<<< orphan*/  cooked_default ; 
 int /*<<< orphan*/  fdwoptions ; 
 int /*<<< orphan*/  generated ; 
 int /*<<< orphan*/  identity ; 
 int /*<<< orphan*/  identitySequence ; 
 int /*<<< orphan*/  inhcount ; 
 int /*<<< orphan*/  is_from_type ; 
 int /*<<< orphan*/  is_local ; 
 int /*<<< orphan*/  is_not_null ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  raw_default ; 
 int /*<<< orphan*/  storage ; 
 int /*<<< orphan*/  typeName ; 

__attribute__((used)) static bool
_equalColumnDef(const ColumnDef *a, const ColumnDef *b)
{
	COMPARE_STRING_FIELD(colname);
	COMPARE_NODE_FIELD(typeName);
	COMPARE_SCALAR_FIELD(inhcount);
	COMPARE_SCALAR_FIELD(is_local);
	COMPARE_SCALAR_FIELD(is_not_null);
	COMPARE_SCALAR_FIELD(is_from_type);
	COMPARE_SCALAR_FIELD(storage);
	COMPARE_NODE_FIELD(raw_default);
	COMPARE_NODE_FIELD(cooked_default);
	COMPARE_SCALAR_FIELD(identity);
	COMPARE_NODE_FIELD(identitySequence);
	COMPARE_SCALAR_FIELD(generated);
	COMPARE_NODE_FIELD(collClause);
	COMPARE_SCALAR_FIELD(collOid);
	COMPARE_NODE_FIELD(constraints);
	COMPARE_NODE_FIELD(fdwoptions);
	COMPARE_LOCATION_FIELD(location);

	return true;
}