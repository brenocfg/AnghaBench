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
typedef  int int32 ;
typedef  int /*<<< orphan*/  WORKSTATE ;

/* Variables and functions */
#define  CLOSE 132 
 int END ; 
#define  ERR 131 
 int /*<<< orphan*/  ERRCODE_STATEMENT_TOO_COMPLEX ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
#define  OPEN 130 
#define  OPR 129 
 int STACKDEPTH ; 
#define  VAL 128 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int gettoken (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pushquery (int /*<<< orphan*/ *,int const,int) ; 

__attribute__((used)) static int32
makepol(WORKSTATE *state)
{
	int32		val,
				type;
	int32		stack[STACKDEPTH];
	int32		lenstack = 0;

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	while ((type = gettoken(state, &val)) != END)
	{
		switch (type)
		{
			case VAL:
				pushquery(state, type, val);
				while (lenstack && (stack[lenstack - 1] == (int32) '&' ||
									stack[lenstack - 1] == (int32) '!'))
				{
					lenstack--;
					pushquery(state, OPR, stack[lenstack]);
				}
				break;
			case OPR:
				if (lenstack && val == (int32) '|')
					pushquery(state, OPR, val);
				else
				{
					if (lenstack == STACKDEPTH)
						ereport(ERROR,
								(errcode(ERRCODE_STATEMENT_TOO_COMPLEX),
								 errmsg("statement too complex")));
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
					pushquery(state, OPR, stack[lenstack]);
				}
				break;
			case CLOSE:
				while (lenstack)
				{
					lenstack--;
					pushquery(state, OPR, stack[lenstack]);
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
		pushquery(state, OPR, stack[lenstack]);
	};
	return END;
}