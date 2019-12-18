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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  GroupingSetData ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  numGroups ; 
 int /*<<< orphan*/  set ; 

__attribute__((used)) static void
_outGroupingSetData(StringInfo str, const GroupingSetData *node)
{
	WRITE_NODE_TYPE("GSDATA");

	WRITE_NODE_FIELD(set);
	WRITE_FLOAT_FIELD(numGroups, "%.0f");
}