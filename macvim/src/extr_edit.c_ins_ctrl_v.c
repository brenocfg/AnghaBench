#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  AppendToRedobuff (int /*<<< orphan*/ *) ; 
 scalar_t__ CTRL_V_STR ; 
 int /*<<< orphan*/  Ctrl_V ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  add_to_showcmd_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  char_avail () ; 
 int /*<<< orphan*/  clear_showcmd () ; 
 int /*<<< orphan*/  edit_putchar (char,int) ; 
 int /*<<< orphan*/  edit_unputchar () ; 
 int get_literal () ; 
 int /*<<< orphan*/  ins_redraw (int) ; 
 int /*<<< orphan*/  insert_special (int,int,int) ; 
 scalar_t__ redrawing () ; 
 int /*<<< orphan*/  revins_chars ; 
 int /*<<< orphan*/  revins_legal ; 

__attribute__((used)) static void
ins_ctrl_v()
{
    int		c;
    int		did_putchar = FALSE;

    /* may need to redraw when no more chars available now */
    ins_redraw(FALSE);

    if (redrawing() && !char_avail())
    {
	edit_putchar('^', TRUE);
	did_putchar = TRUE;
    }
    AppendToRedobuff((char_u *)CTRL_V_STR);	/* CTRL-V */

#ifdef FEAT_CMDL_INFO
    add_to_showcmd_c(Ctrl_V);
#endif

    c = get_literal();
    if (did_putchar)
	/* when the line fits in 'columns' the '^' is at the start of the next
	 * line and will not removed by the redraw */
	edit_unputchar();
#ifdef FEAT_CMDL_INFO
    clear_showcmd();
#endif
    insert_special(c, FALSE, TRUE);
#ifdef FEAT_RIGHTLEFT
    revins_chars++;
    revins_legal++;
#endif
}