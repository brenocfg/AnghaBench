#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  str; int /*<<< orphan*/  core_yystype; } ;
struct TYPE_7__ {int lloc; TYPE_1__ lval; int /*<<< orphan*/  leng; } ;
typedef  TYPE_2__ TokenAuxData ;
struct TYPE_8__ {char* scanbuf; } ;

/* Variables and functions */
 int GREATER_GREATER ; 
 int LESS_LESS ; 
 int Op ; 
 int PARAM ; 
 TYPE_5__ core_yy ; 
 int core_yylex (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 size_t num_pushbacks ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 
 TYPE_2__* pushback_auxdata ; 
 int* pushback_token ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  yyscanner ; 

__attribute__((used)) static int
internal_yylex(TokenAuxData *auxdata)
{
	int			token;
	const char *yytext;

	if (num_pushbacks > 0)
	{
		num_pushbacks--;
		token = pushback_token[num_pushbacks];
		*auxdata = pushback_auxdata[num_pushbacks];
	}
	else
	{
		token = core_yylex(&auxdata->lval.core_yystype,
						   &auxdata->lloc,
						   yyscanner);

		/* remember the length of yytext before it gets changed */
		yytext = core_yy.scanbuf + auxdata->lloc;
		auxdata->leng = strlen(yytext);

		/* Check for << >> and #, which the core considers operators */
		if (token == Op)
		{
			if (strcmp(auxdata->lval.str, "<<") == 0)
				token = LESS_LESS;
			else if (strcmp(auxdata->lval.str, ">>") == 0)
				token = GREATER_GREATER;
			else if (strcmp(auxdata->lval.str, "#") == 0)
				token = '#';
		}

		/* The core returns PARAM as ival, but we treat it like IDENT */
		else if (token == PARAM)
		{
			auxdata->lval.str = pstrdup(yytext);
		}
	}

	return token;
}