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
 int /*<<< orphan*/  exit_gtk_browser (int) ; 
 int /*<<< orphan*/  ui__exit (int) ; 
 int use_browser ; 

void exit_browser(bool wait_for_ok)
{
	switch (use_browser) {
	case 2:
		exit_gtk_browser(wait_for_ok);
		break;

	case 1:
		ui__exit(wait_for_ok);
		break;

	default:
		break;
	}
}