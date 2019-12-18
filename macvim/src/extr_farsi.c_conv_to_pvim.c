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
typedef  int /*<<< orphan*/  linenr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_3__ {int ml_line_count; } ;
struct TYPE_4__ {TYPE_1__ b_ml; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR ; 
 int /*<<< orphan*/  F_isalpha (int /*<<< orphan*/ ) ; 
 scalar_t__ F_isterm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HLF_S ; 
 int /*<<< orphan*/  MSG_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 scalar_t__ canF_Ljoin (int /*<<< orphan*/ ) ; 
 scalar_t__ canF_Rjoin (int /*<<< orphan*/ ) ; 
 TYPE_2__* curbuf ; 
 int /*<<< orphan*/  do_cmdline_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  farsi_text_1 ; 
 int /*<<< orphan*/  hl_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ml_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redraw_later (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toF_Rjoin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toF_TyA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toF_ending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toF_leading (int /*<<< orphan*/ ) ; 

void
conv_to_pvim()
{
    char_u	*ptr;
    int		lnum, llen, i;

    for (lnum = 1; lnum <= curbuf->b_ml.ml_line_count; ++lnum)
    {
	ptr = ml_get((linenr_T)lnum);

	llen = (int)STRLEN(ptr);

	for ( i = 0; i < llen-1; i++)
	{
	    if (canF_Ljoin(ptr[i]) && canF_Rjoin(ptr[i+1]))
	    {
		ptr[i] = toF_leading(ptr[i]);
		++i;

		while (canF_Rjoin(ptr[i]) && i < llen)
		{
		    ptr[i] = toF_Rjoin(ptr[i]);
		    if (F_isterm(ptr[i]) || !F_isalpha(ptr[i]))
			break;
		    ++i;
		}
		if (!F_isalpha(ptr[i]) || !canF_Rjoin(ptr[i]))
		    ptr[i-1] = toF_ending(ptr[i-1]);
	    }
	    else
		ptr[i] = toF_TyA(ptr[i]);
	}
    }

    /*
     * Following lines contains Farsi encoded character.
     */

    do_cmdline_cmd((char_u *)"%s/\202\231/\232/g");
    do_cmdline_cmd((char_u *)"%s/\201\231/\370\334/g");

    /* Assume the screen has been messed up: clear it and redraw. */
    redraw_later(CLEAR);
    MSG_ATTR(farsi_text_1, hl_attr(HLF_S));
}