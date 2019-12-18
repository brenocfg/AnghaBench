#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgssLocationLen ;
struct TYPE_11__ {unsigned char* jumble; int clocations_buf_size; scalar_t__ clocations_count; scalar_t__ jumble_len; scalar_t__ highest_extern_param_id; int /*<<< orphan*/ * clocations; } ;
typedef  TYPE_1__ pgssJumbleState ;
struct TYPE_13__ {int /*<<< orphan*/  p_sourcetext; } ;
struct TYPE_12__ {void* queryId; int /*<<< orphan*/  stmt_len; int /*<<< orphan*/  stmt_location; scalar_t__ utilityStmt; } ;
typedef  TYPE_2__ Query ;
typedef  TYPE_3__ ParseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 void* DatumGetUInt64 (int /*<<< orphan*/ ) ; 
 int JUMBLE_SIZE ; 
 int /*<<< orphan*/  JumbleQuery (TYPE_1__*,TYPE_2__*) ; 
 void* UINT64CONST (int) ; 
 int /*<<< orphan*/  hash_any_extended (unsigned char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pgss ; 
 int /*<<< orphan*/  pgss_enabled () ; 
 int /*<<< orphan*/  pgss_hash ; 
 int /*<<< orphan*/  pgss_store (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  prev_post_parse_analyze_hook (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void
pgss_post_parse_analyze(ParseState *pstate, Query *query)
{
	pgssJumbleState jstate;

	if (prev_post_parse_analyze_hook)
		prev_post_parse_analyze_hook(pstate, query);

	/* Assert we didn't do this already */
	Assert(query->queryId == UINT64CONST(0));

	/* Safety check... */
	if (!pgss || !pgss_hash || !pgss_enabled())
		return;

	/*
	 * Utility statements get queryId zero.  We do this even in cases where
	 * the statement contains an optimizable statement for which a queryId
	 * could be derived (such as EXPLAIN or DECLARE CURSOR).  For such cases,
	 * runtime control will first go through ProcessUtility and then the
	 * executor, and we don't want the executor hooks to do anything, since we
	 * are already measuring the statement's costs at the utility level.
	 */
	if (query->utilityStmt)
	{
		query->queryId = UINT64CONST(0);
		return;
	}

	/* Set up workspace for query jumbling */
	jstate.jumble = (unsigned char *) palloc(JUMBLE_SIZE);
	jstate.jumble_len = 0;
	jstate.clocations_buf_size = 32;
	jstate.clocations = (pgssLocationLen *)
		palloc(jstate.clocations_buf_size * sizeof(pgssLocationLen));
	jstate.clocations_count = 0;
	jstate.highest_extern_param_id = 0;

	/* Compute query ID and mark the Query node with it */
	JumbleQuery(&jstate, query);
	query->queryId =
		DatumGetUInt64(hash_any_extended(jstate.jumble, jstate.jumble_len, 0));

	/*
	 * If we are unlucky enough to get a hash of zero, use 1 instead, to
	 * prevent confusion with the utility-statement case.
	 */
	if (query->queryId == UINT64CONST(0))
		query->queryId = UINT64CONST(1);

	/*
	 * If we were able to identify any ignorable constants, we immediately
	 * create a hash table entry for the query, so that we can record the
	 * normalized form of the query string.  If there were no such constants,
	 * the normalized string would be the same as the query text anyway, so
	 * there's no need for an early entry.
	 */
	if (jstate.clocations_count > 0)
		pgss_store(pstate->p_sourcetext,
				   query->queryId,
				   query->stmt_location,
				   query->stmt_len,
				   0,
				   0,
				   NULL,
				   &jstate);
}