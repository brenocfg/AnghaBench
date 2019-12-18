#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ts_tokentype ;
typedef  int /*<<< orphan*/  int8 ;
typedef  int int16 ;
struct TYPE_5__ {int state; char* buf; int in_quotes; int /*<<< orphan*/  valstate; } ;
typedef  TYPE_1__* TSQueryParserState ;

/* Variables and functions */
 int /*<<< orphan*/  ISOPERATOR (char*) ; 
 int /*<<< orphan*/  OP_AND ; 
 int /*<<< orphan*/  OP_NOT ; 
 int /*<<< orphan*/  OP_OR ; 
 int /*<<< orphan*/  OP_PHRASE ; 
 int /*<<< orphan*/  PT_CLOSE ; 
 int /*<<< orphan*/  PT_END ; 
 int /*<<< orphan*/  PT_OPEN ; 
 int /*<<< orphan*/  PT_OPR ; 
 int /*<<< orphan*/  PT_VAL ; 
#define  WAITFIRSTOPERAND 130 
#define  WAITOPERAND 129 
#define  WAITOPERATOR 128 
 int /*<<< orphan*/  gettoken_tsvector (int /*<<< orphan*/ ,char**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  parse_or_operator (TYPE_1__*) ; 
 scalar_t__ pg_mblen (char*) ; 
 int /*<<< orphan*/  pushStop (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_tsvector_parser (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  t_iseq (char*,char) ; 
 int /*<<< orphan*/  t_isspace (char*) ; 

__attribute__((used)) static ts_tokentype
gettoken_query_websearch(TSQueryParserState state, int8 *operator,
						 int *lenval, char **strval,
						 int16 *weight, bool *prefix)
{
	*weight = 0;
	*prefix = false;

	while (true)
	{
		switch (state->state)
		{
			case WAITFIRSTOPERAND:
			case WAITOPERAND:
				if (t_iseq(state->buf, '-'))
				{
					state->buf++;
					state->state = WAITOPERAND;

					if (state->in_quotes)
						continue;

					*operator = OP_NOT;
					return PT_OPR;
				}
				else if (t_iseq(state->buf, '"'))
				{
					state->buf++;

					if (!state->in_quotes)
					{
						state->state = WAITOPERAND;

						if (strchr(state->buf, '"'))
						{
							/* quoted text should be ordered <-> */
							state->in_quotes = true;
							return PT_OPEN;
						}

						/* web search tolerates missing quotes */
						continue;
					}
					else
					{
						/* we have to provide an operand */
						state->in_quotes = false;
						state->state = WAITOPERATOR;
						pushStop(state);
						return PT_CLOSE;
					}
				}
				else if (ISOPERATOR(state->buf))
				{
					/* or else gettoken_tsvector() will raise an error */
					state->buf++;
					state->state = WAITOPERAND;
					continue;
				}
				else if (!t_isspace(state->buf))
				{
					/*
					 * We rely on the tsvector parser to parse the value for
					 * us
					 */
					reset_tsvector_parser(state->valstate, state->buf);
					if (gettoken_tsvector(state->valstate, strval, lenval,
										  NULL, NULL, &state->buf))
					{
						state->state = WAITOPERATOR;
						return PT_VAL;
					}
					else if (state->state == WAITFIRSTOPERAND)
					{
						return PT_END;
					}
					else
					{
						/* finally, we have to provide an operand */
						pushStop(state);
						return PT_END;
					}
				}
				break;

			case WAITOPERATOR:
				if (t_iseq(state->buf, '"'))
				{
					if (!state->in_quotes)
					{
						/*
						 * put implicit AND after an operand and handle this
						 * quote in WAITOPERAND
						 */
						state->state = WAITOPERAND;
						*operator = OP_AND;
						return PT_OPR;
					}
					else
					{
						state->buf++;

						/* just close quotes */
						state->in_quotes = false;
						return PT_CLOSE;
					}
				}
				else if (parse_or_operator(state))
				{
					state->state = WAITOPERAND;
					*operator = OP_OR;
					return PT_OPR;
				}
				else if (*state->buf == '\0')
				{
					return PT_END;
				}
				else if (!t_isspace(state->buf))
				{
					if (state->in_quotes)
					{
						/* put implicit <-> after an operand */
						*operator = OP_PHRASE;
						*weight = 1;
					}
					else
					{
						/* put implicit AND after an operand */
						*operator = OP_AND;
					}

					state->state = WAITOPERAND;
					return PT_OPR;
				}
				break;
		}

		state->buf += pg_mblen(state->buf);
	}
}