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
typedef  int /*<<< orphan*/  RangeVar ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  catalogname ; 
 int /*<<< orphan*/  inh ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  relname ; 
 int /*<<< orphan*/  relpersistence ; 
 int /*<<< orphan*/  schemaname ; 

__attribute__((used)) static bool
_equalRangeVar(const RangeVar *a, const RangeVar *b)
{
	COMPARE_STRING_FIELD(catalogname);
	COMPARE_STRING_FIELD(schemaname);
	COMPARE_STRING_FIELD(relname);
	COMPARE_SCALAR_FIELD(inh);
	COMPARE_SCALAR_FIELD(relpersistence);
	COMPARE_NODE_FIELD(alias);
	COMPARE_LOCATION_FIELD(location);

	return true;
}