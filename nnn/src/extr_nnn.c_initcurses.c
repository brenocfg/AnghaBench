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
typedef  int /*<<< orphan*/  mmask_t ;
struct TYPE_4__ {scalar_t__ picker; } ;
struct TYPE_3__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int BUTTON1_DOUBLE_CLICKED ; 
 int BUTTON1_PRESSED ; 
 int BUTTON4_PRESSED ; 
 int BUTTON5_PRESSED ; 
 short CTX_MAX ; 
 int /*<<< orphan*/  DPRINTF_S (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  cbreak () ; 
 TYPE_2__ cfg ; 
 int /*<<< orphan*/  curs_set (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* g_ctx ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  init_pair (short,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mouseinterval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousemask (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newterm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 int /*<<< orphan*/  set_escdelay (int) ; 
 int /*<<< orphan*/  settimeout () ; 
 int /*<<< orphan*/  start_color () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  use_default_colors () ; 

__attribute__((used)) static bool initcurses(mmask_t *oldmask)
{
	short i;

	if (cfg.picker) {
		if (!newterm(NULL, stderr, stdin)) {
			fprintf(stderr, "newterm!\n");
			return FALSE;
		}
	} else if (!initscr()) {
		fprintf(stderr, "initscr!\n");
		DPRINTF_S(getenv("TERM"));
		return FALSE;
	}

	cbreak();
	noecho();
	nonl();
	//intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
#if NCURSES_MOUSE_VERSION <= 1
	mousemask(BUTTON1_PRESSED | BUTTON1_DOUBLE_CLICKED, oldmask);
#else
	mousemask(BUTTON1_PRESSED | BUTTON4_PRESSED | BUTTON5_PRESSED,
		  oldmask);
#endif
	mouseinterval(0);
	curs_set(FALSE); /* Hide cursor */
	start_color();
	use_default_colors();

	/* Initialize default colors */
	for (i = 0; i <  CTX_MAX; ++i)
		init_pair(i + 1, g_ctx[i].color, -1);

	settimeout(); /* One second */
	set_escdelay(25);
	return TRUE;
}