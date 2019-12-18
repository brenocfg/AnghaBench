#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lastRes; TYPE_1__* tmpRes; } ;
struct TYPE_6__ {struct TYPE_6__* lexeme; } ;
typedef  TYPE_1__ TSLexeme ;
typedef  int /*<<< orphan*/  ParsedLex ;
typedef  TYPE_2__ LexizeData ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
setNewTmpRes(LexizeData *ld, ParsedLex *lex, TSLexeme *res)
{
	if (ld->tmpRes)
	{
		TSLexeme   *ptr;

		for (ptr = ld->tmpRes; ptr->lexeme; ptr++)
			pfree(ptr->lexeme);
		pfree(ld->tmpRes);
	}
	ld->tmpRes = res;
	ld->lastRes = lex;
}