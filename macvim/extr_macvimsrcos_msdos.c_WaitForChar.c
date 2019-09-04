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

/* Variables and functions */
 long BIOSTICK ; 
 int FALSE ; 
 long FOREVER ; 
 int TRUE ; 
 scalar_t__ bioskey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioskey_ready ; 
 long biostime (int /*<<< orphan*/ ,long) ; 
 scalar_t__ cbrk_pressed ; 
 scalar_t__ cons_kbhit () ; 
 scalar_t__ kbhit () ; 
 scalar_t__ p_biosk ; 
 scalar_t__ p_consk ; 

__attribute__((used)) static  int
WaitForChar(long msec)
{
    long	starttime = 0;

    if (msec != 0)
	starttime = biostime(0, 0L);

    for (;;)
    {
#ifdef FEAT_MOUSE
	long		clicktime;
	static int	old_status = 0;
	union REGS	regs;
	int		x, y;

	if (mouse_avail && mouse_active && mouse_click < 0)
	{
	    regs.x.ax = 3;
	    int86(0x33, &regs, &regs);	    /* check mouse status */
		/* only recognize button-down and button-up event */
	    x = regs.x.cx / mouse_x_div;
	    y = regs.x.dx / mouse_y_div;
	    if ((old_status == 0) != (regs.x.bx == 0))
	    {
		if (old_status)	/* button up */
		    mouse_click = MOUSE_RELEASE;
		else			/* button down */
		{
		    /*
		     * Translate MSDOS mouse events to Vim mouse events.
		     * TODO: should handle middle mouse button, by pressing
		     * left and right at the same time.
		     */
		    if (regs.x.bx & MSDOS_MOUSE_LEFT)
			mouse_click = MOUSE_LEFT;
		    else if (regs.x.bx & MSDOS_MOUSE_RIGHT)
			mouse_click = MOUSE_RIGHT;
		    else if (regs.x.bx & MSDOS_MOUSE_MIDDLE)
			mouse_click = MOUSE_MIDDLE;

		    /*
		     * Find out if this is a multi-click
		     */
		    clicktime = biostime(0, 0L);
		    if (mouse_click_x == x && mouse_click_y == y
			    && mouse_topline == curwin->w_topline
#ifdef FEAT_DIFF
			    && mouse_topfill == curwin->w_topfill
#endif
			    && mouse_click_count != 4
			    && mouse_click == mouse_last_click
			    && clicktime < mouse_click_time
							+ p_mouset / BIOSTICK)
			++mouse_click_count;
		    else
			mouse_click_count = 1;
		    mouse_click_time = clicktime;
		    mouse_last_click = mouse_click;
		    mouse_click_x = x;
		    mouse_click_y = y;
		    mouse_topline = curwin->w_topline;
#ifdef FEAT_DIFF
		    mouse_topfill = curwin->w_topfill;
#endif
		    SET_NUM_MOUSE_CLICKS(mouse_click, mouse_click_count);
		}
	    }
	    else if (old_status && (x != mouse_x || y != mouse_y))
		mouse_click = MOUSE_DRAG;
	    old_status = regs.x.bx;
	    if (mouse_hidden && mouse_x >= 0 && (mouse_x != x || mouse_y != y))
	    {
		mouse_hidden = FALSE;
		show_mouse(TRUE);
	    }
	    mouse_x = x;
	    mouse_y = y;
	}
#endif

	if ((p_consk ? cons_kbhit()
				 : p_biosk ? bioskey(bioskey_ready) : kbhit())
		|| cbrk_pressed
#ifdef FEAT_MOUSE
						    || mouse_click >= 0
#endif
		)
	    return TRUE;
	/*
	 * Use biostime() to wait until our time is done.
	 * We busy-wait here.  Unfortunately, delay() and usleep() have been
	 * reported to give problems with the original Windows 95.  This is
	 * fixed in service pack 1, but not everybody installed that.
	 * The DJGPP implementation of usleep() uses a busy-wait loop too.
	 */
	if (msec == 0 || (msec != FOREVER
			    && biostime(0, 0L) > starttime + msec / BIOSTICK))
	    break;

#ifdef DJGPP
	/* Yield the CPU to the next process. */
	__dpmi_yield();
#endif
    }
    return FALSE;
}