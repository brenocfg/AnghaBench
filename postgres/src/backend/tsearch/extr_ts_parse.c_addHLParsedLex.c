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
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_13__ {scalar_t__ vectorpos; } ;
struct TYPE_12__ {scalar_t__ type; int flags; struct TYPE_12__* lexeme; struct TYPE_12__* next; int /*<<< orphan*/  lenlemm; int /*<<< orphan*/  lemm; } ;
typedef  int /*<<< orphan*/  TSQuery ;
typedef  TYPE_1__ TSLexeme ;
typedef  TYPE_1__ ParsedLex ;
typedef  TYPE_3__ HeadlineParsedText ;

/* Variables and functions */
 int TSL_ADDPOS ; 
 int /*<<< orphan*/  hladdword (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hlfinditem (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (TYPE_1__*) ; 

__attribute__((used)) static void
addHLParsedLex(HeadlineParsedText *prs, TSQuery query, ParsedLex *lexs, TSLexeme *norms)
{
	ParsedLex  *tmplexs;
	TSLexeme   *ptr;
	int32		savedpos;

	while (lexs)
	{
		if (lexs->type > 0)
			hladdword(prs, lexs->lemm, lexs->lenlemm, lexs->type);

		ptr = norms;
		savedpos = prs->vectorpos;
		while (ptr && ptr->lexeme)
		{
			if (ptr->flags & TSL_ADDPOS)
				savedpos++;
			hlfinditem(prs, query, savedpos, ptr->lexeme, strlen(ptr->lexeme));
			ptr++;
		}

		tmplexs = lexs->next;
		pfree(lexs);
		lexs = tmplexs;
	}

	if (norms)
	{
		ptr = norms;
		while (ptr->lexeme)
		{
			if (ptr->flags & TSL_ADDPOS)
				prs->vectorpos++;
			pfree(ptr->lexeme);
			ptr++;
		}
		pfree(norms);
	}
}