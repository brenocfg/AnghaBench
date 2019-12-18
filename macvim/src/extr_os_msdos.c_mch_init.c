#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ax; int cx; } ;
struct TYPE_6__ {int ah; int bh; int bl; int al; } ;
union REGS {TYPE_2__ x; TYPE_1__ h; } ;
struct TYPE_8__ {int ax; } ;
struct TYPE_9__ {TYPE_3__ x; } ;
typedef  TYPE_4__ __dpmi_regs ;

/* Variables and functions */
 int Columns ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  O_BINARY ; 
 int Rows ; 
 int /*<<< orphan*/  TRUE ; 
 int __dpmi_int (int,TYPE_4__*) ; 
 int /*<<< orphan*/  _fmode ; 
 scalar_t__ bioskey_read ; 
 int bioskey_ready ; 
 int /*<<< orphan*/  clip_init (int /*<<< orphan*/ ) ; 
 int cterm_normal_bg_color ; 
 int cterm_normal_fg_color ; 
 int /*<<< orphan*/  get_screenbase () ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  int86 (int,union REGS*,union REGS*) ; 
 int /*<<< orphan*/  mch_get_shellsize () ; 
 int /*<<< orphan*/  mch_restore_cursor_shape (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mch_update_cursor () ; 
 int mouse_avail ; 
 int mouse_x_div ; 
 int mouse_y_div ; 
 int /*<<< orphan*/  mynormvideo () ; 
 int orig_attr ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  set_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_console ; 

void
mch_init(void)
{
    union REGS regs;

#if defined(DJGPP) && defined(FEAT_CLIPBOARD)
    __dpmi_regs  dpmi_regs;
#endif

    /*
     * Get the video attributes at the cursor.  These will be used as the
     * default attributes.
     */
    regs.h.ah = 0x08;
    regs.h.bh = 0x00;		/* video page 0 */
    int86(0x10, &regs, &regs);
    orig_attr = regs.h.ah;
    mynormvideo();
    if (cterm_normal_fg_color == 0)
	cterm_normal_fg_color = (orig_attr & 0xf) + 1;
    if (cterm_normal_bg_color == 0)
	cterm_normal_bg_color = ((orig_attr >> 4) & 0xf) + 1;

    term_console = TRUE;    /* assume using the console for the things here */
    _fmode = O_BINARY;	    /* we do our own CR-LF translation */
    out_flush();
    set_interrupts(TRUE);   /* catch interrupts */

#ifdef DJGPP
    /*
     * Use Long File Names by default, if $LFN not set.
     */
    if (getenv("LFN") == NULL)
	putenv("LFN=y");

    get_screenbase();
#endif

#ifdef FEAT_MOUSE
/* find out if a MS compatible mouse is available */
    regs.x.ax = 0;
    (void)int86(0x33, &regs, &regs);
    mouse_avail = regs.x.ax;
    /* best guess for mouse coordinate computations */
    mch_get_shellsize();
    if (Columns <= 40)
	mouse_x_div = 16;
    if (Rows == 30)
	mouse_y_div = 16;
#endif

    /*
     * Try switching to 16 colors for background, instead of 8 colors and
     * blinking.  Does this always work?  Can the old value be restored?
     */
    regs.x.ax = 0x1003;
    regs.h.bl = 0x00;
    regs.h.bh = 0x00;
    int86(0x10, &regs, &regs);

    /*
     * Test if we have an enhanced AT keyboard.  Write 0xFFFF to the keyboard
     * buffer and try to read it back.  If we can't in 16 tries, it's an old
     * type XT keyboard.
     */
    regs.h.ah = 0x05;
    regs.x.cx = 0xffff;
    int86(0x16, &regs, &regs);
    if (regs.h.al != 1)	/* skip this when keyboard buffer is full */
    {
	int i;

	for (i = 0; i < 16; ++i)
	{
	    regs.h.ah = 0x10;
	    int86(0x16, &regs, &regs);
	    if (regs.x.ax == 0xffff)
		break;
	}
	if (i == 16)	/* 0xffff not read, must be old keyboard */
	{
	    bioskey_read = 0;
	    bioskey_ready = 1;
	}
    }

#ifdef MCH_CURSOR_SHAPE
    /* Save the old cursor shape */
    mch_restore_cursor_shape(FALSE);
    /* Initialise the cursor shape */
    mch_update_cursor();
#endif

#if defined(DJGPP) && defined(FEAT_CLIPBOARD)
    /*
     * Check to see if the Windows clipboard is available, ie. are we
     * running from a DOS session within Windows.  Obviously, the Windows
     * clipboard will not be available if we're running under pure DOS.
     *
     * int 0x2f, AX = 0x1700 identifies the Windows version we're running
     * under.  Upon return from the interrupt, if AX is unchanged, we're
     * running under pure DOS and no Windows clipboard is available.
     *
     * Remark: could use int86() here but __dpmi_int() is recommended in
     * the DJGPP docs, since int86() doesn't cover all available interrupts.
     */
    dpmi_regs.x.ax = 0x1700;
    if (__dpmi_int(0x2f, &dpmi_regs) == -1)
	/* real-mode interrupt failed? */
	dpmi_regs.x.ax = 0x1700;	/* force failure */

    if (dpmi_regs.x.ax == 0x1700)	/* no change in AX? */
	clip_init(FALSE);		/* no clipboard available, too bad */
    else				/* else, running under Windows, OK */
	clip_init(TRUE);		/* clipboard is available */
#endif
}