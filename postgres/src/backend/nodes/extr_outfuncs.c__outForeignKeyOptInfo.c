#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nkeys; int /*<<< orphan*/ * rinfos; int /*<<< orphan*/ ** eclass; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ ForeignKeyOptInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ATTRNUMBER_ARRAY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  con_relid ; 
 int /*<<< orphan*/  confkey ; 
 int /*<<< orphan*/  conkey ; 
 int /*<<< orphan*/  conpfeqop ; 
 int /*<<< orphan*/  list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nkeys ; 
 int /*<<< orphan*/  nmatched_ec ; 
 int /*<<< orphan*/  nmatched_rcols ; 
 int /*<<< orphan*/  nmatched_ri ; 
 int /*<<< orphan*/  ref_relid ; 

__attribute__((used)) static void
_outForeignKeyOptInfo(StringInfo str, const ForeignKeyOptInfo *node)
{
	int			i;

	WRITE_NODE_TYPE("FOREIGNKEYOPTINFO");

	WRITE_UINT_FIELD(con_relid);
	WRITE_UINT_FIELD(ref_relid);
	WRITE_INT_FIELD(nkeys);
	WRITE_ATTRNUMBER_ARRAY(conkey, node->nkeys);
	WRITE_ATTRNUMBER_ARRAY(confkey, node->nkeys);
	WRITE_OID_ARRAY(conpfeqop, node->nkeys);
	WRITE_INT_FIELD(nmatched_ec);
	WRITE_INT_FIELD(nmatched_rcols);
	WRITE_INT_FIELD(nmatched_ri);
	/* for compactness, just print the number of matches per column: */
	appendStringInfoString(str, " :eclass");
	for (i = 0; i < node->nkeys; i++)
		appendStringInfo(str, " %d", (node->eclass[i] != NULL));
	appendStringInfoString(str, " :rinfos");
	for (i = 0; i < node->nkeys; i++)
		appendStringInfo(str, " %d", list_length(node->rinfos[i]));
}