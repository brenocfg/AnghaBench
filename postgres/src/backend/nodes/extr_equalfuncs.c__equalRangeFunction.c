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
typedef  int /*<<< orphan*/  RangeFunction ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  coldeflist ; 
 int /*<<< orphan*/  functions ; 
 int /*<<< orphan*/  is_rowsfrom ; 
 int /*<<< orphan*/  lateral ; 
 int /*<<< orphan*/  ordinality ; 

__attribute__((used)) static bool
_equalRangeFunction(const RangeFunction *a, const RangeFunction *b)
{
	COMPARE_SCALAR_FIELD(lateral);
	COMPARE_SCALAR_FIELD(ordinality);
	COMPARE_SCALAR_FIELD(is_rowsfrom);
	COMPARE_NODE_FIELD(functions);
	COMPARE_NODE_FIELD(alias);
	COMPARE_NODE_FIELD(coldeflist);

	return true;
}