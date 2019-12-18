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
typedef  int /*<<< orphan*/  GroupingFunc ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agglevelsup ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  cols ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  refs ; 

__attribute__((used)) static void
_outGroupingFunc(StringInfo str, const GroupingFunc *node)
{
	WRITE_NODE_TYPE("GROUPINGFUNC");

	WRITE_NODE_FIELD(args);
	WRITE_NODE_FIELD(refs);
	WRITE_NODE_FIELD(cols);
	WRITE_UINT_FIELD(agglevelsup);
	WRITE_LOCATION_FIELD(location);
}