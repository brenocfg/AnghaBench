#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* curline; int /*<<< orphan*/  fp; int /*<<< orphan*/  lineno; } ;
typedef  TYPE_1__ tsearch_readline_state ;

/* Variables and functions */
 char* t_readline (int /*<<< orphan*/ ) ; 

char *
tsearch_readline(tsearch_readline_state *stp)
{
	char	   *result;

	stp->lineno++;
	stp->curline = NULL;
	result = t_readline(stp->fp);
	stp->curline = result;
	return result;
}