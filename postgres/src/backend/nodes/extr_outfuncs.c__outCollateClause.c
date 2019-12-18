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
typedef  int /*<<< orphan*/  CollateClause ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  arg ; 
 int /*<<< orphan*/  collname ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static void
_outCollateClause(StringInfo str, const CollateClause *node)
{
	WRITE_NODE_TYPE("COLLATECLAUSE");

	WRITE_NODE_FIELD(arg);
	WRITE_NODE_FIELD(collname);
	WRITE_LOCATION_FIELD(location);
}