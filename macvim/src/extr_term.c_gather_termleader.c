#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ in_use; } ;
struct TYPE_3__ {int /*<<< orphan*/ * code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI ; 
 int /*<<< orphan*/  DCS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NUL ; 
 scalar_t__ check_for_codes ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  need_gather ; 
 int tc_len ; 
 TYPE_1__* termcodes ; 
 int /*<<< orphan*/ * termleader ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gather_termleader()
{
    int	    i;
    int	    len = 0;

#ifdef FEAT_GUI
    if (gui.in_use)
	termleader[len++] = CSI;    /* the GUI codes are not in termcodes[] */
#endif
#ifdef FEAT_TERMRESPONSE
    if (check_for_codes)
	termleader[len++] = DCS;    /* the termcode response starts with DCS
				       in 8-bit mode */
#endif
    termleader[len] = NUL;

    for (i = 0; i < tc_len; ++i)
	if (vim_strchr(termleader, termcodes[i].code[0]) == NULL)
	{
	    termleader[len++] = termcodes[i].code[0];
	    termleader[len] = NUL;
	}

    need_gather = FALSE;
}