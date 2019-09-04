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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  handle_tab_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_tab_next (int /*<<< orphan*/ *) ; 
 scalar_t__ handle_tab_nth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  handle_tab_prev (int /*<<< orphan*/ *) ; 
 int r_cons_any_key (char*) ; 

__attribute__((used)) static bool handle_tab(RCore *core) {
	int ch = r_cons_any_key ("[Tab] nkey:nth; p:prev; n:next; t:new");
	if (handle_tab_nth (core, ch)) {
		return true;
	}
	switch (ch) {
		case 'n':
			if (handle_tab_next (core)) {
				return true;
			}
			break;
		case 'p':
			if (handle_tab_prev (core)) {
				return true;
			}
			break;
		case 't':
			(void)handle_tab_new (core);
			break;
	}
	return false;
}