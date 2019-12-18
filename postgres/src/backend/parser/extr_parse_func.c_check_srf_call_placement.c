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
struct TYPE_4__ {int p_expr_kind; int p_hasTargetSRFs; int /*<<< orphan*/ * p_last_srf; } ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
#define  EXPR_KIND_ALTER_COL_TRANSFORM 168 
#define  EXPR_KIND_CALL_ARGUMENT 167 
#define  EXPR_KIND_CHECK_CONSTRAINT 166 
#define  EXPR_KIND_COLUMN_DEFAULT 165 
#define  EXPR_KIND_COPY_WHERE 164 
#define  EXPR_KIND_DISTINCT_ON 163 
#define  EXPR_KIND_DOMAIN_CHECK 162 
#define  EXPR_KIND_EXECUTE_PARAMETER 161 
#define  EXPR_KIND_FILTER 160 
#define  EXPR_KIND_FROM_FUNCTION 159 
#define  EXPR_KIND_FROM_SUBSELECT 158 
#define  EXPR_KIND_FUNCTION_DEFAULT 157 
#define  EXPR_KIND_GENERATED_COLUMN 156 
#define  EXPR_KIND_GROUP_BY 155 
#define  EXPR_KIND_HAVING 154 
#define  EXPR_KIND_INDEX_EXPRESSION 153 
#define  EXPR_KIND_INDEX_PREDICATE 152 
#define  EXPR_KIND_INSERT_TARGET 151 
#define  EXPR_KIND_JOIN_ON 150 
#define  EXPR_KIND_JOIN_USING 149 
#define  EXPR_KIND_LIMIT 148 
#define  EXPR_KIND_NONE 147 
#define  EXPR_KIND_OFFSET 146 
#define  EXPR_KIND_ORDER_BY 145 
#define  EXPR_KIND_OTHER 144 
#define  EXPR_KIND_PARTITION_BOUND 143 
#define  EXPR_KIND_PARTITION_EXPRESSION 142 
#define  EXPR_KIND_POLICY 141 
#define  EXPR_KIND_RETURNING 140 
#define  EXPR_KIND_SELECT_TARGET 139 
#define  EXPR_KIND_TRIGGER_WHEN 138 
#define  EXPR_KIND_UPDATE_SOURCE 137 
#define  EXPR_KIND_UPDATE_TARGET 136 
#define  EXPR_KIND_VALUES 135 
#define  EXPR_KIND_VALUES_SINGLE 134 
#define  EXPR_KIND_WHERE 133 
#define  EXPR_KIND_WINDOW_FRAME_GROUPS 132 
#define  EXPR_KIND_WINDOW_FRAME_RANGE 131 
#define  EXPR_KIND_WINDOW_FRAME_ROWS 130 
#define  EXPR_KIND_WINDOW_ORDER 129 
#define  EXPR_KIND_WINDOW_PARTITION 128 
 int /*<<< orphan*/  ParseExprKindName (int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char const*) ; 
 int exprLocation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_1__*,int) ; 

void
check_srf_call_placement(ParseState *pstate, Node *last_srf, int location)
{
	const char *err;
	bool		errkind;

	/*
	 * Check to see if the set-returning function is in an invalid place
	 * within the query.  Basically, we don't allow SRFs anywhere except in
	 * the targetlist (which includes GROUP BY/ORDER BY expressions), VALUES,
	 * and functions in FROM.
	 *
	 * For brevity we support two schemes for reporting an error here: set
	 * "err" to a custom message, or set "errkind" true if the error context
	 * is sufficiently identified by what ParseExprKindName will return, *and*
	 * what it will return is just a SQL keyword.  (Otherwise, use a custom
	 * message to avoid creating translation problems.)
	 */
	err = NULL;
	errkind = false;
	switch (pstate->p_expr_kind)
	{
		case EXPR_KIND_NONE:
			Assert(false);		/* can't happen */
			break;
		case EXPR_KIND_OTHER:
			/* Accept SRF here; caller must throw error if wanted */
			break;
		case EXPR_KIND_JOIN_ON:
		case EXPR_KIND_JOIN_USING:
			err = _("set-returning functions are not allowed in JOIN conditions");
			break;
		case EXPR_KIND_FROM_SUBSELECT:
			/* can't get here, but just in case, throw an error */
			errkind = true;
			break;
		case EXPR_KIND_FROM_FUNCTION:
			/* okay, but we don't allow nested SRFs here */
			/* errmsg is chosen to match transformRangeFunction() */
			/* errposition should point to the inner SRF */
			if (pstate->p_last_srf != last_srf)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("set-returning functions must appear at top level of FROM"),
						 parser_errposition(pstate,
											exprLocation(pstate->p_last_srf))));
			break;
		case EXPR_KIND_WHERE:
			errkind = true;
			break;
		case EXPR_KIND_POLICY:
			err = _("set-returning functions are not allowed in policy expressions");
			break;
		case EXPR_KIND_HAVING:
			errkind = true;
			break;
		case EXPR_KIND_FILTER:
			errkind = true;
			break;
		case EXPR_KIND_WINDOW_PARTITION:
		case EXPR_KIND_WINDOW_ORDER:
			/* okay, these are effectively GROUP BY/ORDER BY */
			pstate->p_hasTargetSRFs = true;
			break;
		case EXPR_KIND_WINDOW_FRAME_RANGE:
		case EXPR_KIND_WINDOW_FRAME_ROWS:
		case EXPR_KIND_WINDOW_FRAME_GROUPS:
			err = _("set-returning functions are not allowed in window definitions");
			break;
		case EXPR_KIND_SELECT_TARGET:
		case EXPR_KIND_INSERT_TARGET:
			/* okay */
			pstate->p_hasTargetSRFs = true;
			break;
		case EXPR_KIND_UPDATE_SOURCE:
		case EXPR_KIND_UPDATE_TARGET:
			/* disallowed because it would be ambiguous what to do */
			errkind = true;
			break;
		case EXPR_KIND_GROUP_BY:
		case EXPR_KIND_ORDER_BY:
			/* okay */
			pstate->p_hasTargetSRFs = true;
			break;
		case EXPR_KIND_DISTINCT_ON:
			/* okay */
			pstate->p_hasTargetSRFs = true;
			break;
		case EXPR_KIND_LIMIT:
		case EXPR_KIND_OFFSET:
			errkind = true;
			break;
		case EXPR_KIND_RETURNING:
			errkind = true;
			break;
		case EXPR_KIND_VALUES:
			/* SRFs are presently not supported by nodeValuesscan.c */
			errkind = true;
			break;
		case EXPR_KIND_VALUES_SINGLE:
			/* okay, since we process this like a SELECT tlist */
			pstate->p_hasTargetSRFs = true;
			break;
		case EXPR_KIND_CHECK_CONSTRAINT:
		case EXPR_KIND_DOMAIN_CHECK:
			err = _("set-returning functions are not allowed in check constraints");
			break;
		case EXPR_KIND_COLUMN_DEFAULT:
		case EXPR_KIND_FUNCTION_DEFAULT:
			err = _("set-returning functions are not allowed in DEFAULT expressions");
			break;
		case EXPR_KIND_INDEX_EXPRESSION:
			err = _("set-returning functions are not allowed in index expressions");
			break;
		case EXPR_KIND_INDEX_PREDICATE:
			err = _("set-returning functions are not allowed in index predicates");
			break;
		case EXPR_KIND_ALTER_COL_TRANSFORM:
			err = _("set-returning functions are not allowed in transform expressions");
			break;
		case EXPR_KIND_EXECUTE_PARAMETER:
			err = _("set-returning functions are not allowed in EXECUTE parameters");
			break;
		case EXPR_KIND_TRIGGER_WHEN:
			err = _("set-returning functions are not allowed in trigger WHEN conditions");
			break;
		case EXPR_KIND_PARTITION_BOUND:
			err = _("set-returning functions are not allowed in partition bound");
			break;
		case EXPR_KIND_PARTITION_EXPRESSION:
			err = _("set-returning functions are not allowed in partition key expressions");
			break;
		case EXPR_KIND_CALL_ARGUMENT:
			err = _("set-returning functions are not allowed in CALL arguments");
			break;
		case EXPR_KIND_COPY_WHERE:
			err = _("set-returning functions are not allowed in COPY FROM WHERE conditions");
			break;
		case EXPR_KIND_GENERATED_COLUMN:
			err = _("set-returning functions are not allowed in column generation expressions");
			break;

			/*
			 * There is intentionally no default: case here, so that the
			 * compiler will warn if we add a new ParseExprKind without
			 * extending this switch.  If we do see an unrecognized value at
			 * runtime, the behavior will be the same as for EXPR_KIND_OTHER,
			 * which is sane anyway.
			 */
	}
	if (err)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg_internal("%s", err),
				 parser_errposition(pstate, location)));
	if (errkind)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
		/* translator: %s is name of a SQL construct, eg GROUP BY */
				 errmsg("set-returning functions are not allowed in %s",
						ParseExprKindName(pstate->p_expr_kind)),
				 parser_errposition(pstate, location)));
}