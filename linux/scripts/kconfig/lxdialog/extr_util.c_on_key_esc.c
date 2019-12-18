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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int ERR ; 
 int /*<<< orphan*/  FALSE ; 
 int KEY_ESC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ungetch (int) ; 
 int wgetch (int /*<<< orphan*/ *) ; 

int on_key_esc(WINDOW *win)
{
	int key;
	int key2;
	int key3;

	nodelay(win, TRUE);
	keypad(win, FALSE);
	key = wgetch(win);
	key2 = wgetch(win);
	do {
		key3 = wgetch(win);
	} while (key3 != ERR);
	nodelay(win, FALSE);
	keypad(win, TRUE);
	if (key == KEY_ESC && key2 == ERR)
		return KEY_ESC;
	else if (key != ERR && key != KEY_ESC && key2 == ERR)
		ungetch(key);

	return -1;
}