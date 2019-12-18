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
typedef  int /*<<< orphan*/  RollupData ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  groupClause ; 
 int /*<<< orphan*/  gsets ; 
 int /*<<< orphan*/  gsets_data ; 
 int /*<<< orphan*/  hashable ; 
 int /*<<< orphan*/  is_hashed ; 
 int /*<<< orphan*/  numGroups ; 

__attribute__((used)) static void
_outRollupData(StringInfo str, const RollupData *node)
{
	WRITE_NODE_TYPE("ROLLUP");

	WRITE_NODE_FIELD(groupClause);
	WRITE_NODE_FIELD(gsets);
	WRITE_NODE_FIELD(gsets_data);
	WRITE_FLOAT_FIELD(numGroups, "%.0f");
	WRITE_BOOL_FIELD(hashable);
	WRITE_BOOL_FIELD(is_hashed);
}