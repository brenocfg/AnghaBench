#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16 ;
struct TYPE_5__ {int reslen; TYPE_2__* res; } ;
typedef  TYPE_1__ TheSubstitute ;
struct TYPE_6__ {int /*<<< orphan*/ * lexeme; } ;
typedef  TYPE_2__ TSLexeme ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/ * pstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TSLexeme *
copyTSLexeme(TheSubstitute *ts)
{
	TSLexeme   *res;
	uint16		i;

	res = (TSLexeme *) palloc(sizeof(TSLexeme) * (ts->reslen + 1));
	for (i = 0; i < ts->reslen; i++)
	{
		res[i] = ts->res[i];
		res[i].lexeme = pstrdup(ts->res[i].lexeme);
	}

	res[ts->reslen].lexeme = NULL;

	return res;
}