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
 int /*<<< orphan*/  HLF_S ; 
 int /*<<< orphan*/  MSG_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 TYPE_2__* curbuf ; 
 int /*<<< orphan*/  do_cmdline_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  farsi_text_2 ; 
 int /*<<< orphan*/  hl_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ml_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redraw_later (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toF_TyA (int /*<<< orphan*/ ) ; 

void
conv_to_pstd()
{
    char_u	*ptr;
    int		lnum, llen, i;

    /*
     * Following line contains Farsi encoded character.
     */

    do_cmdline_cmd((char_u *)"%s/\232/\202\231/g");

    for (lnum = 1; lnum <= curbuf->b_ml.ml_line_count; ++lnum)
    {
	ptr = ml_get((linenr_T)lnum);

	llen = (int)STRLEN(ptr);

	for ( i = 0; i < llen; i++)
	{
	    ptr[i] = toF_TyA(ptr[i]);

	}
    }

    /* Assume the screen has been messed up: clear it and redraw. */
    redraw_later(CLEAR);
    MSG_ATTR(farsi_text_2, hl_attr(HLF_S));
}