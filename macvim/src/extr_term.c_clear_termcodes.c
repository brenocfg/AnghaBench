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
struct TYPE_3__ {struct TYPE_3__* code; } ;

/* Variables and functions */
 char* BC ; 
 int /*<<< orphan*/  NUL ; 
 int /*<<< orphan*/  PC ; 
 int /*<<< orphan*/  TRUE ; 
 char* UP ; 
 scalar_t__ empty_option ; 
 int /*<<< orphan*/  need_gather ; 
 scalar_t__ ospeed ; 
 size_t tc_len ; 
 scalar_t__ tc_max_len ; 
 TYPE_1__* termcodes ; 
 int /*<<< orphan*/  vim_free (TYPE_1__*) ; 

void
clear_termcodes()
{
    while (tc_len > 0)
	vim_free(termcodes[--tc_len].code);
    vim_free(termcodes);
    termcodes = NULL;
    tc_max_len = 0;

#ifdef HAVE_TGETENT
    BC = (char *)empty_option;
    UP = (char *)empty_option;
    PC = NUL;			/* set pad character to NUL */
    ospeed = 0;
#endif

    need_gather = TRUE;		/* need to fill termleader[] */
}