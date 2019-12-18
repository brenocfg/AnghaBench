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
typedef  int /*<<< orphan*/  SubLink ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  operName ; 
 int /*<<< orphan*/  subLinkId ; 
 int /*<<< orphan*/  subLinkType ; 
 int /*<<< orphan*/  subselect ; 
 int /*<<< orphan*/  testexpr ; 

__attribute__((used)) static bool
_equalSubLink(const SubLink *a, const SubLink *b)
{
	COMPARE_SCALAR_FIELD(subLinkType);
	COMPARE_SCALAR_FIELD(subLinkId);
	COMPARE_NODE_FIELD(testexpr);
	COMPARE_NODE_FIELD(operName);
	COMPARE_NODE_FIELD(subselect);
	COMPARE_LOCATION_FIELD(location);

	return true;
}