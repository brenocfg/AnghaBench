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
typedef  int /*<<< orphan*/  WindowDef ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endOffset ; 
 int /*<<< orphan*/  frameOptions ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  orderClause ; 
 int /*<<< orphan*/  partitionClause ; 
 int /*<<< orphan*/  refname ; 
 int /*<<< orphan*/  startOffset ; 

__attribute__((used)) static void
_outWindowDef(StringInfo str, const WindowDef *node)
{
	WRITE_NODE_TYPE("WINDOWDEF");

	WRITE_STRING_FIELD(name);
	WRITE_STRING_FIELD(refname);
	WRITE_NODE_FIELD(partitionClause);
	WRITE_NODE_FIELD(orderClause);
	WRITE_INT_FIELD(frameOptions);
	WRITE_NODE_FIELD(startOffset);
	WRITE_NODE_FIELD(endOffset);
	WRITE_LOCATION_FIELD(location);
}