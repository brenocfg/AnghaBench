#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ magic; int is_complete; int /*<<< orphan*/  query_list; int /*<<< orphan*/ * resultDesc; } ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHEDPLANSOURCE_MAGIC ; 
 int /*<<< orphan*/ * FetchStatementTargetList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * QueryListGetPrimaryStmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RevalidateCachedQuery (TYPE_1__*,int /*<<< orphan*/ *) ; 

List *
CachedPlanGetTargetList(CachedPlanSource *plansource,
						QueryEnvironment *queryEnv)
{
	Query	   *pstmt;

	/* Assert caller is doing things in a sane order */
	Assert(plansource->magic == CACHEDPLANSOURCE_MAGIC);
	Assert(plansource->is_complete);

	/*
	 * No work needed if statement doesn't return tuples (we assume this
	 * feature cannot be changed by an invalidation)
	 */
	if (plansource->resultDesc == NULL)
		return NIL;

	/* Make sure the querytree list is valid and we have parse-time locks */
	RevalidateCachedQuery(plansource, queryEnv);

	/* Get the primary statement and find out what it returns */
	pstmt = QueryListGetPrimaryStmt(plansource->query_list);

	return FetchStatementTargetList((Node *) pstmt);
}