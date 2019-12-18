#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tp_ch_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ROWS_AVAIL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compute_cmdrow () ; 
 TYPE_1__* curtab ; 
 int /*<<< orphan*/  curwin ; 
 int /*<<< orphan*/ * firstwin ; 
 int /*<<< orphan*/  frame_check_height (int /*<<< orphan*/ ,int) ; 
 int frame_minheight (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_new_height (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_ch ; 
 scalar_t__ p_ea ; 
 int /*<<< orphan*/  topframe ; 
 int /*<<< orphan*/  win_comp_pos () ; 
 int /*<<< orphan*/  win_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  win_new_height (int /*<<< orphan*/ *,int) ; 

void
shell_new_rows()
{
    int		h = (int)ROWS_AVAIL;

    if (firstwin == NULL)	/* not initialized yet */
	return;
#ifdef FEAT_WINDOWS
    if (h < frame_minheight(topframe, NULL))
	h = frame_minheight(topframe, NULL);

    /* First try setting the heights of windows with 'winfixheight'.  If
     * that doesn't result in the right height, forget about that option. */
    frame_new_height(topframe, h, FALSE, TRUE);
    if (!frame_check_height(topframe, h))
	frame_new_height(topframe, h, FALSE, FALSE);

    (void)win_comp_pos();		/* recompute w_winrow and w_wincol */
#else
    if (h < 1)
	h = 1;
    win_new_height(firstwin, h);
#endif
    compute_cmdrow();
#ifdef FEAT_WINDOWS
    curtab->tp_ch_used = p_ch;
#endif

#if 0
    /* Disabled: don't want making the screen smaller make a window larger. */
    if (p_ea)
	win_equal(curwin, FALSE, 'v');
#endif
}