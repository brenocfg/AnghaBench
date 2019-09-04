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
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SL_KEY_UNTAB ; 
 int SLang_init_tty (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLkp_define_keysym (char*,int /*<<< orphan*/ ) ; 
 int SLkp_init () ; 
 int SLsmg_init_smg () ; 
 int /*<<< orphan*/  SLtt_get_screen_size () ; 
 int /*<<< orphan*/  SLtt_get_terminfo () ; 
 int /*<<< orphan*/  SLutf8_enable (int) ; 
 int /*<<< orphan*/  hist_browser__init_hpp () ; 
 int /*<<< orphan*/  perf_error__register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_tui_eops ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_progress__init () ; 
 int /*<<< orphan*/  ui__signal ; 
 int /*<<< orphan*/  ui__signal_backtrace ; 
 int /*<<< orphan*/  ui_browser__init () ; 
 int /*<<< orphan*/  ui_helpline__init () ; 

int ui__init(void)
{
	int err;

	SLutf8_enable(-1);
	SLtt_get_terminfo();
	SLtt_get_screen_size();

	err = SLsmg_init_smg();
	if (err < 0)
		goto out;
	err = SLang_init_tty(-1, 0, 0);
	if (err < 0)
		goto out;

	err = SLkp_init();
	if (err < 0) {
		pr_err("TUI initialization failed.\n");
		goto out;
	}

	SLkp_define_keysym((char *)"^(kB)", SL_KEY_UNTAB);

	signal(SIGSEGV, ui__signal_backtrace);
	signal(SIGFPE, ui__signal_backtrace);
	signal(SIGINT, ui__signal);
	signal(SIGQUIT, ui__signal);
	signal(SIGTERM, ui__signal);

	perf_error__register(&perf_tui_eops);

	ui_helpline__init();
	ui_browser__init();
	tui_progress__init();

	hist_browser__init_hpp();
out:
	return err;
}