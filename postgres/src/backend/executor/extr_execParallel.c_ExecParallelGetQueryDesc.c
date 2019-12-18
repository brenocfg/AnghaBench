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
typedef  int /*<<< orphan*/  shm_toc ;
typedef  int /*<<< orphan*/  QueryDesc ;
typedef  int /*<<< orphan*/  PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateQueryDesc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetActiveSnapshot () ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 int /*<<< orphan*/  PARALLEL_KEY_PARAMLISTINFO ; 
 int /*<<< orphan*/  PARALLEL_KEY_PLANNEDSTMT ; 
 int /*<<< orphan*/  PARALLEL_KEY_QUERY_TEXT ; 
 int /*<<< orphan*/  RestoreParamList (char**) ; 
 char* shm_toc_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stringToNode (char*) ; 

__attribute__((used)) static QueryDesc *
ExecParallelGetQueryDesc(shm_toc *toc, DestReceiver *receiver,
						 int instrument_options)
{
	char	   *pstmtspace;
	char	   *paramspace;
	PlannedStmt *pstmt;
	ParamListInfo paramLI;
	char	   *queryString;

	/* Get the query string from shared memory */
	queryString = shm_toc_lookup(toc, PARALLEL_KEY_QUERY_TEXT, false);

	/* Reconstruct leader-supplied PlannedStmt. */
	pstmtspace = shm_toc_lookup(toc, PARALLEL_KEY_PLANNEDSTMT, false);
	pstmt = (PlannedStmt *) stringToNode(pstmtspace);

	/* Reconstruct ParamListInfo. */
	paramspace = shm_toc_lookup(toc, PARALLEL_KEY_PARAMLISTINFO, false);
	paramLI = RestoreParamList(&paramspace);

	/* Create a QueryDesc for the query. */
	return CreateQueryDesc(pstmt,
						   queryString,
						   GetActiveSnapshot(), InvalidSnapshot,
						   receiver, paramLI, NULL, instrument_options);
}