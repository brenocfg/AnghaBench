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
typedef  int /*<<< orphan*/  MultiAssignRef ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  colno ; 
 int /*<<< orphan*/  ncolumns ; 
 int /*<<< orphan*/  source ; 

__attribute__((used)) static void
_outMultiAssignRef(StringInfo str, const MultiAssignRef *node)
{
	WRITE_NODE_TYPE("MULTIASSIGNREF");

	WRITE_NODE_FIELD(source);
	WRITE_INT_FIELD(colno);
	WRITE_INT_FIELD(ncolumns);
}