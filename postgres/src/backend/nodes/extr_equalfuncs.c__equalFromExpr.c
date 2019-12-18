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
typedef  int /*<<< orphan*/  FromExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fromlist ; 
 int /*<<< orphan*/  quals ; 

__attribute__((used)) static bool
_equalFromExpr(const FromExpr *a, const FromExpr *b)
{
	COMPARE_NODE_FIELD(fromlist);
	COMPARE_NODE_FIELD(quals);

	return true;
}