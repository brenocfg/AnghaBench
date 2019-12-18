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
typedef  int /*<<< orphan*/  YYSTYPE ;
typedef  int /*<<< orphan*/  YYLTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  BETWEEN 139 
#define  FIRST_P 138 
#define  ILIKE 137 
#define  IN_P 136 
#define  LAST_P 135 
#define  LIKE 134 
#define  NOT 133 
 int NOT_LA ; 
 int NULLS_LA ; 
#define  NULLS_P 132 
#define  ORDINALITY 131 
#define  SIMILAR 130 
#define  TIME 129 
#define  WITH 128 
 int WITH_LA ; 
 int base_yylex () ; 
 int /*<<< orphan*/  base_yylloc ; 
 int /*<<< orphan*/  base_yylval ; 
 char* base_yytext ; 
 int have_lookahead ; 
 char* lookahead_end ; 
 char lookahead_hold_char ; 
 int lookahead_token ; 
 int /*<<< orphan*/  lookahead_yylloc ; 
 int /*<<< orphan*/  lookahead_yylval ; 
 char* lookahead_yytext ; 

int
filtered_base_yylex(void)
{
	int			cur_token;
	int			next_token;
	int			cur_token_length;
	YYSTYPE		cur_yylval;
	YYLTYPE		cur_yylloc;
	char	   *cur_yytext;

	/* Get next token --- we might already have it */
	if (have_lookahead)
	{
		cur_token = lookahead_token;
		base_yylval = lookahead_yylval;
		base_yylloc = lookahead_yylloc;
		base_yytext = lookahead_yytext;
		*lookahead_end = lookahead_hold_char;
		have_lookahead = false;
	}
	else
		cur_token = base_yylex();

	/*
	 * If this token isn't one that requires lookahead, just return it.  If it
	 * does, determine the token length.  (We could get that via strlen(), but
	 * since we have such a small set of possibilities, hardwiring seems
	 * feasible and more efficient.)
	 */
	switch (cur_token)
	{
		case NOT:
			cur_token_length = 3;
			break;
		case NULLS_P:
			cur_token_length = 5;
			break;
		case WITH:
			cur_token_length = 4;
			break;
		default:
			return cur_token;
	}

	/*
	 * Identify end+1 of current token.  base_yylex() has temporarily stored a
	 * '\0' here, and will undo that when we call it again.  We need to redo
	 * it to fully revert the lookahead call for error reporting purposes.
	 */
	lookahead_end = base_yytext + cur_token_length;
	Assert(*lookahead_end == '\0');

	/* Save and restore lexer output variables around the call */
	cur_yylval = base_yylval;
	cur_yylloc = base_yylloc;
	cur_yytext = base_yytext;

	/* Get next token, saving outputs into lookahead variables */
	next_token = base_yylex();

	lookahead_token = next_token;
	lookahead_yylval = base_yylval;
	lookahead_yylloc = base_yylloc;
	lookahead_yytext = base_yytext;

	base_yylval = cur_yylval;
	base_yylloc = cur_yylloc;
	base_yytext = cur_yytext;

	/* Now revert the un-truncation of the current token */
	lookahead_hold_char = *lookahead_end;
	*lookahead_end = '\0';

	have_lookahead = true;

	/* Replace cur_token if needed, based on lookahead */
	switch (cur_token)
	{
		case NOT:
			/* Replace NOT by NOT_LA if it's followed by BETWEEN, IN, etc */
			switch (next_token)
			{
				case BETWEEN:
				case IN_P:
				case LIKE:
				case ILIKE:
				case SIMILAR:
					cur_token = NOT_LA;
					break;
			}
			break;

		case NULLS_P:
			/* Replace NULLS_P by NULLS_LA if it's followed by FIRST or LAST */
			switch (next_token)
			{
				case FIRST_P:
				case LAST_P:
					cur_token = NULLS_LA;
					break;
			}
			break;

		case WITH:
			/* Replace WITH by WITH_LA if it's followed by TIME or ORDINALITY */
			switch (next_token)
			{
				case TIME:
				case ORDINALITY:
					cur_token = WITH_LA;
					break;
			}
			break;
	}

	return cur_token;
}