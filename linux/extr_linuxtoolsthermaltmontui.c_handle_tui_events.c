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
typedef  int /*<<< orphan*/  PANEL ;

/* Variables and functions */
 int EOF ; 
#define  KEY_LEFT 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  box (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cooling_device_window ; 
 int /*<<< orphan*/  data_panel ; 
 int dialogue_on ; 
 int /*<<< orphan*/ * dialogue_panel ; 
 int /*<<< orphan*/  dialogue_window ; 
 int /*<<< orphan*/  doupdate () ; 
 int /*<<< orphan*/  handle_input_choice (int) ; 
 int /*<<< orphan*/  input_lock ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ panel_userptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_control_w () ; 
 int /*<<< orphan*/  show_data_w () ; 
 int /*<<< orphan*/  show_dialogue () ; 
 int tmon_exit ; 
 int /*<<< orphan*/ * top ; 
 int /*<<< orphan*/  top_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_panels () ; 
 int wgetch (int /*<<< orphan*/ ) ; 

void *handle_tui_events(void *arg)
{
	int ch;

	keypad(cooling_device_window, TRUE);
	while ((ch = wgetch(cooling_device_window)) != EOF) {
		if (tmon_exit)
			break;
		/* when term size is too small, no dialogue panels are set.
		 * we need to filter out such cases.
		 */
		if (!data_panel || !dialogue_panel ||
			!cooling_device_window ||
			!dialogue_window) {

			continue;
		}
		pthread_mutex_lock(&input_lock);
		if (dialogue_on) {
			handle_input_choice(ch);
			/* top panel filter */
			if (ch == 'q' || ch == 'Q')
				ch = 0;
		}
		switch (ch) {
		case KEY_LEFT:
			box(cooling_device_window, 10, 0);
			break;
		case 9: /* TAB */
			top = (PANEL *)panel_userptr(top);
			top_panel(top);
			if (top == dialogue_panel) {
				dialogue_on = 1;
				show_dialogue();
			} else {
				dialogue_on = 0;
				/* force refresh */
				show_data_w();
				show_control_w();
			}
			break;
		case 'q':
		case 'Q':
			tmon_exit = 1;
			break;
		}
		update_panels();
		doupdate();
		pthread_mutex_unlock(&input_lock);
	}

	if (arg)
		*(int *)arg = 0; /* make gcc happy */

	return NULL;
}