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
typedef  int /*<<< orphan*/  RangeTableFunc ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  columns ; 
 int /*<<< orphan*/  docexpr ; 
 int /*<<< orphan*/  lateral ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  namespaces ; 
 int /*<<< orphan*/  rowexpr ; 

__attribute__((used)) static bool
_equalRangeTableFunc(const RangeTableFunc *a, const RangeTableFunc *b)
{
	COMPARE_SCALAR_FIELD(lateral);
	COMPARE_NODE_FIELD(docexpr);
	COMPARE_NODE_FIELD(rowexpr);
	COMPARE_NODE_FIELD(namespaces);
	COMPARE_NODE_FIELD(columns);
	COMPARE_NODE_FIELD(alias);
	COMPARE_LOCATION_FIELD(location);

	return true;
}