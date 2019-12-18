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
typedef  int /*<<< orphan*/  IndexOptInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypothetical ; 
 int /*<<< orphan*/  immediate ; 
 int /*<<< orphan*/  indexoid ; 
 int /*<<< orphan*/  indextlist ; 
 int /*<<< orphan*/  indpred ; 
 int /*<<< orphan*/  indrestrictinfo ; 
 int /*<<< orphan*/  ncolumns ; 
 int /*<<< orphan*/  pages ; 
 int /*<<< orphan*/  predOK ; 
 int /*<<< orphan*/  relam ; 
 int /*<<< orphan*/  tree_height ; 
 int /*<<< orphan*/  tuples ; 
 int /*<<< orphan*/  unique ; 

__attribute__((used)) static void
_outIndexOptInfo(StringInfo str, const IndexOptInfo *node)
{
	WRITE_NODE_TYPE("INDEXOPTINFO");

	/* NB: this isn't a complete set of fields */
	WRITE_OID_FIELD(indexoid);
	/* Do NOT print rel field, else infinite recursion */
	WRITE_UINT_FIELD(pages);
	WRITE_FLOAT_FIELD(tuples, "%.0f");
	WRITE_INT_FIELD(tree_height);
	WRITE_INT_FIELD(ncolumns);
	/* array fields aren't really worth the trouble to print */
	WRITE_OID_FIELD(relam);
	/* indexprs is redundant since we print indextlist */
	WRITE_NODE_FIELD(indpred);
	WRITE_NODE_FIELD(indextlist);
	WRITE_NODE_FIELD(indrestrictinfo);
	WRITE_BOOL_FIELD(predOK);
	WRITE_BOOL_FIELD(unique);
	WRITE_BOOL_FIELD(immediate);
	WRITE_BOOL_FIELD(hypothetical);
	/* we don't bother with fields copied from the index AM's API struct */
}