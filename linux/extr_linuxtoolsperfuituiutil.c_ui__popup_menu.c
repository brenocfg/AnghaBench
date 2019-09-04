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
struct ui_browser {void* entries; int nr_entries; int /*<<< orphan*/  write; int /*<<< orphan*/  seek; int /*<<< orphan*/  refresh; } ;

/* Variables and functions */
 int popup_menu__run (struct ui_browser*) ; 
 int /*<<< orphan*/  ui_browser__argv_refresh ; 
 int /*<<< orphan*/  ui_browser__argv_seek ; 
 int /*<<< orphan*/  ui_browser__argv_write ; 

int ui__popup_menu(int argc, char * const argv[])
{
	struct ui_browser menu = {
		.entries    = (void *)argv,
		.refresh    = ui_browser__argv_refresh,
		.seek	    = ui_browser__argv_seek,
		.write	    = ui_browser__argv_write,
		.nr_entries = argc,
	};

	return popup_menu__run(&menu);
}