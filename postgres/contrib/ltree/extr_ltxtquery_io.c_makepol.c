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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  QPRS_STATE ;

/* Variables and functions */
#define  CLOSE 132 
 int END ; 
#define  ERR 131 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
#define  OPEN 130 
#define  OPR 129 
 int STACKDEPTH ; 
#define  VAL 128 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int gettoken_query (int /*<<< orphan*/ *,int*,int*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pushquery (int /*<<< orphan*/ *,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushval_asis (int /*<<< orphan*/ *,int const,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32
makepol(QPRS_STATE *state)
{
	int32		val = 0,
				type;
	int32		lenval = 0;
	char	   *strval = NULL;
	int32		stack[STACKDEPTH];
	int32		lenstack = 0;
	uint16		flag = 0;

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	while ((type = gettoken_query(state, &val, &lenval, &strval, &flag)) != END)
	{
		switch (type)
		{
			case VAL:
				pushval_asis(state, VAL, strval, lenval, flag);
				while (lenstack && (stack[lenstack - 1] == (int32) '&' ||
									stack[lenstack - 1] == (int32) '!'))
				{
					lenstack--;
					pushquery(state, OPR, stack[lenstack], 0, 0, 0);
				}
				break;
			case OPR:
				if (lenstack && val == (int32) '|')
					pushquery(state, OPR, val, 0, 0, 0);
				else
				{
					if (lenstack == STACKDEPTH)
						/* internal error */
						elog(ERROR, "stack too short");
					stack[lenstack] = val;
					lenstack++;
				}
				break;
			case OPEN:
				if (makepol(state) == ERR)
					return ERR;
				while (lenstack && (stack[lenstack - 1] == (int32) '&' ||
									stack[lenstack - 1] == (int32) '!'))
				{
					lenstack--;
					pushquery(state, OPR, stack[lenstack], 0, 0, 0);
				}
				break;
			case CLOSE:
				while (lenstack)
				{
					lenstack--;
					pushquery(state, OPR, stack[lenstack], 0, 0, 0);
				};
				return END;
				break;
			case ERR:
			default:
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("syntax error")));

				return ERR;

		}
	}
	while (lenstack)
	{
		lenstack--;
		pushquery(state, OPR, stack[lenstack], 0, 0, 0);
	};
	return END;
}