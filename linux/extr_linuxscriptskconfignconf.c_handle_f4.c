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
 int btn_dialog (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 int /*<<< orphan*/  main_window ; 
 int show_all_items ; 

__attribute__((used)) static void handle_f4(int *key, struct menu *current_item)
{
	int res = btn_dialog(main_window,
			"Show all symbols?",
			2,
			"   <Show All>   ",
			"<Don't show all>");
	if (res == 0)
		show_all_items = 1;
	else if (res == 1)
		show_all_items = 0;

	return;
}