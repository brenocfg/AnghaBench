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
 char* PERF_GTK_DSO ; 
 scalar_t__ dump_trace ; 
 int /*<<< orphan*/  isatty (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setup_gtk_browser () ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  ui__init () ; 
 int use_browser ; 

void setup_browser(bool fallback_to_pager)
{
	if (use_browser < 2 && (!isatty(1) || dump_trace))
		use_browser = 0;

	/* default to TUI */
	if (use_browser < 0)
		use_browser = 1;

	switch (use_browser) {
	case 2:
		if (setup_gtk_browser() == 0)
			break;
		printf("GTK browser requested but could not find %s\n",
		       PERF_GTK_DSO);
		sleep(1);
		use_browser = 1;
		/* fall through */
	case 1:
		if (ui__init() == 0)
			break;
		/* fall through */
	default:
		use_browser = 0;
		if (fallback_to_pager)
			setup_pager();
		break;
	}
}