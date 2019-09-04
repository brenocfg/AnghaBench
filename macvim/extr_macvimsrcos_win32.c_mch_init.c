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
struct TYPE_3__ {int wAttributes; } ;
typedef  scalar_t__ PFNGCKLN ;
typedef  TYPE_1__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetConsoleCursorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetModuleHandle (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int O_BINARY ; 
 int /*<<< orphan*/  SEM_FAILCRITICALERRORS ; 
 int /*<<< orphan*/  SET_INVALID_PARAM_HANDLER ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetErrorMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_conin () ; 
 int cterm_normal_bg_color ; 
 int cterm_normal_fg_color ; 
 int g_attrCurrent ; 
 int g_attrDefault ; 
 int /*<<< orphan*/  g_cci ; 
 int /*<<< orphan*/  g_cmodein ; 
 int /*<<< orphan*/  g_cmodeout ; 
 int /*<<< orphan*/  g_fWindInitCalled ; 
 int /*<<< orphan*/  g_hConIn ; 
 int /*<<< orphan*/  g_hConOut ; 
 int /*<<< orphan*/  out_flush () ; 
 scalar_t__ read_cmd_fd ; 
 scalar_t__ s_pfnGetConsoleKeyboardLayoutName ; 
 int /*<<< orphan*/  ui_get_shellsize () ; 
 int /*<<< orphan*/  update_tcap (int) ; 

void
mch_init(void)
{
#ifndef FEAT_RESTORE_ORIG_SCREEN
    CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif
#ifndef __MINGW32__
    extern int _fmode;
#endif

    /* Silently handle invalid parameters to CRT functions */
    SET_INVALID_PARAM_HANDLER;

    /* Let critical errors result in a failure, not in a dialog box.  Required
     * for the timestamp test to work on removed floppies. */
    SetErrorMode(SEM_FAILCRITICALERRORS);

    _fmode = O_BINARY;		/* we do our own CR-LF translation */
    out_flush();

    /* Obtain handles for the standard Console I/O devices */
    if (read_cmd_fd == 0)
	g_hConIn =  GetStdHandle(STD_INPUT_HANDLE);
    else
	create_conin();
    g_hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

#ifdef FEAT_RESTORE_ORIG_SCREEN
    /* Save the initial console buffer for later restoration */
    SaveConsoleBuffer(&g_cbOrig);
    g_attrCurrent = g_attrDefault = g_cbOrig.Info.wAttributes;
#else
    /* Get current text attributes */
    GetConsoleScreenBufferInfo(g_hConOut, &csbi);
    g_attrCurrent = g_attrDefault = csbi.wAttributes;
#endif
    if (cterm_normal_fg_color == 0)
	cterm_normal_fg_color = (g_attrCurrent & 0xf) + 1;
    if (cterm_normal_bg_color == 0)
	cterm_normal_bg_color = ((g_attrCurrent >> 4) & 0xf) + 1;

    /* set termcap codes to current text attributes */
    update_tcap(g_attrCurrent);

    GetConsoleCursorInfo(g_hConOut, &g_cci);
    GetConsoleMode(g_hConIn,  &g_cmodein);
    GetConsoleMode(g_hConOut, &g_cmodeout);

#ifdef FEAT_TITLE
    SaveConsoleTitleAndIcon();
    /*
     * Set both the small and big icons of the console window to Vim's icon.
     * Note that Vim presently only has one size of icon (32x32), but it
     * automatically gets scaled down to 16x16 when setting the small icon.
     */
    if (g_fCanChangeIcon)
	SetConsoleIcon(g_hWnd, g_hVimIcon, g_hVimIcon);
#endif

    ui_get_shellsize();

#ifdef MCH_WRITE_DUMP
    fdDump = fopen("dump", "wt");

    if (fdDump)
    {
	time_t t;

	time(&t);
	fputs(ctime(&t), fdDump);
	fflush(fdDump);
    }
#endif

    g_fWindInitCalled = TRUE;

#ifdef FEAT_MOUSE
    g_fMouseAvail = GetSystemMetrics(SM_MOUSEPRESENT);
#endif

#ifdef FEAT_CLIPBOARD
    win_clip_init();
#endif

    /* This will be NULL on anything but NT 4.0 */
    s_pfnGetConsoleKeyboardLayoutName =
	(PFNGCKLN) GetProcAddress(GetModuleHandle("kernel32.dll"),
				  "GetConsoleKeyboardLayoutNameA");
}