#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_9__ {TYPE_3__* entries; int /*<<< orphan*/ * lexeme; } ;
typedef  TYPE_1__ TheLexeme ;
struct TYPE_11__ {int tnvariant; int /*<<< orphan*/ * nextentry; int /*<<< orphan*/  posinsubst; int /*<<< orphan*/  idsubst; } ;
struct TYPE_10__ {scalar_t__ lexeme; } ;
typedef  TYPE_2__ TSLexeme ;
typedef  TYPE_3__ LexemeInfo ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/ * pstrdup (scalar_t__) ; 
 scalar_t__ repalloc (TYPE_1__*,int) ; 

__attribute__((used)) static TheLexeme *
addCompiledLexeme(TheLexeme *newwrds, int *nnw, int *tnm, TSLexeme *lexeme, LexemeInfo *src, uint16 tnvariant)
{
	if (*nnw >= *tnm)
	{
		*tnm *= 2;
		newwrds = (TheLexeme *) repalloc(newwrds, sizeof(TheLexeme) * *tnm);
	}

	newwrds[*nnw].entries = (LexemeInfo *) palloc(sizeof(LexemeInfo));

	if (lexeme && lexeme->lexeme)
	{
		newwrds[*nnw].lexeme = pstrdup(lexeme->lexeme);
		newwrds[*nnw].entries->tnvariant = tnvariant;
	}
	else
	{
		newwrds[*nnw].lexeme = NULL;
		newwrds[*nnw].entries->tnvariant = 1;
	}

	newwrds[*nnw].entries->idsubst = src->idsubst;
	newwrds[*nnw].entries->posinsubst = src->posinsubst;

	newwrds[*nnw].entries->nextentry = NULL;

	(*nnw)++;
	return newwrds;
}