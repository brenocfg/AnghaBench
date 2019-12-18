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
struct menu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  main_window ; 
 int /*<<< orphan*/  nconf_global_help ; 
 int /*<<< orphan*/  show_scroll_win (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_f1(int *key, struct menu *current_item)
{
	show_scroll_win(main_window,
			"Global help", nconf_global_help);
	return;
}