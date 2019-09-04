#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_9__ {scalar_t__ bKeyDown; } ;
struct TYPE_7__ {TYPE_6__ KeyEvent; } ;
struct TYPE_8__ {scalar_t__ EventType; TYPE_1__ Event; } ;
typedef  TYPE_2__ INPUT_RECORD ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ FOCUS_EVENT ; 
 scalar_t__ GetTickCount () ; 
 scalar_t__ INFINITE ; 
 scalar_t__ KEY_EVENT ; 
 int TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WINDOW_BUFFER_SIZE_EVENT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ decode_key_event (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_hConIn ; 
 int /*<<< orphan*/  handle_focus_event (TYPE_2__) ; 
 int /*<<< orphan*/  peek_console_input (int /*<<< orphan*/ ,TYPE_2__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  read_console_input (int /*<<< orphan*/ ,TYPE_2__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  shell_resized () ; 

__attribute__((used)) static int
WaitForChar(long msec)
{
    DWORD	    dwNow = 0, dwEndTime = 0;
    INPUT_RECORD    ir;
    DWORD	    cRecords;
    char_u	    ch, ch2;

    if (msec > 0)
	/* Wait until the specified time has elapsed. */
	dwEndTime = GetTickCount() + msec;
    else if (msec < 0)
	/* Wait forever. */
	dwEndTime = INFINITE;

    /* We need to loop until the end of the time period, because
     * we might get multiple unusable mouse events in that time.
     */
    for (;;)
    {
#ifdef FEAT_MZSCHEME
	mzvim_check_threads();
#endif
#ifdef FEAT_CLIENTSERVER
	serverProcessPendingMessages();
#endif
	if (0
#ifdef FEAT_MOUSE
		|| g_nMouseClick != -1
#endif
#ifdef FEAT_CLIENTSERVER
		|| input_available()
#endif
	   )
	    return TRUE;

	if (msec > 0)
	{
	    /* If the specified wait time has passed, return.  Beware that
	     * GetTickCount() may wrap around (overflow). */
	    dwNow = GetTickCount();
	    if ((int)(dwNow - dwEndTime) >= 0)
		break;
	}
	if (msec != 0)
	{
	    DWORD dwWaitTime = dwEndTime - dwNow;

#ifdef FEAT_MZSCHEME
	    if (mzthreads_allowed() && p_mzq > 0
				    && (msec < 0 || (long)dwWaitTime > p_mzq))
		dwWaitTime = p_mzq; /* don't wait longer than 'mzquantum' */
#endif
#ifdef FEAT_CLIENTSERVER
	    /* Wait for either an event on the console input or a message in
	     * the client-server window. */
	    if (MsgWaitForMultipleObjects(1, &g_hConIn, FALSE,
				 dwWaitTime, QS_SENDMESSAGE) != WAIT_OBJECT_0)
#else
	    if (WaitForSingleObject(g_hConIn, dwWaitTime) != WAIT_OBJECT_0)
#endif
		    continue;
	}

	cRecords = 0;
	peek_console_input(g_hConIn, &ir, 1, &cRecords);

#ifdef FEAT_MBYTE_IME
	if (State & CMDLINE && msg_row == Rows - 1)
	{
	    CONSOLE_SCREEN_BUFFER_INFO csbi;

	    if (GetConsoleScreenBufferInfo(g_hConOut, &csbi))
	    {
		if (csbi.dwCursorPosition.Y != msg_row)
		{
		    /* The screen is now messed up, must redraw the
		     * command line and later all the windows. */
		    redraw_all_later(CLEAR);
		    cmdline_row -= (msg_row - csbi.dwCursorPosition.Y);
		    redrawcmd();
		}
	    }
	}
#endif

	if (cRecords > 0)
	{
	    if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
	    {
#ifdef FEAT_MBYTE_IME
		/* Windows IME sends two '\n's with only one 'ENTER'.  First:
		 * wVirtualKeyCode == 13. second: wVirtualKeyCode == 0 */
		if (ir.Event.KeyEvent.uChar.UnicodeChar == 0
			&& ir.Event.KeyEvent.wVirtualKeyCode == 13)
		{
		    read_console_input(g_hConIn, &ir, 1, &cRecords);
		    continue;
		}
#endif
		if (decode_key_event(&ir.Event.KeyEvent, &ch, &ch2,
								 NULL, FALSE))
		    return TRUE;
	    }

	    read_console_input(g_hConIn, &ir, 1, &cRecords);

	    if (ir.EventType == FOCUS_EVENT)
		handle_focus_event(ir);
	    else if (ir.EventType == WINDOW_BUFFER_SIZE_EVENT)
		shell_resized();
#ifdef FEAT_MOUSE
	    else if (ir.EventType == MOUSE_EVENT
		    && decode_mouse_event(&ir.Event.MouseEvent))
		return TRUE;
#endif
	}
	else if (msec == 0)
	    break;
    }

#ifdef FEAT_CLIENTSERVER
    /* Something might have been received while we were waiting. */
    if (input_available())
	return TRUE;
#endif
    return FALSE;
}