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
typedef  int /*<<< orphan*/  IndexClause ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  indexcol ; 
 int /*<<< orphan*/  indexcols ; 
 int /*<<< orphan*/  indexquals ; 
 int /*<<< orphan*/  lossy ; 
 int /*<<< orphan*/  rinfo ; 

__attribute__((used)) static void
_outIndexClause(StringInfo str, const IndexClause *node)
{
	WRITE_NODE_TYPE("INDEXCLAUSE");

	WRITE_NODE_FIELD(rinfo);
	WRITE_NODE_FIELD(indexquals);
	WRITE_BOOL_FIELD(lossy);
	WRITE_INT_FIELD(indexcol);
	WRITE_NODE_FIELD(indexcols);
}