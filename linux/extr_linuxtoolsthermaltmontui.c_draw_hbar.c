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
 int MAX_DISP_TEMP ; 
 int TDATA_LEFT ; 
 int /*<<< orphan*/  mvwaddch (int /*<<< orphan*/ *,int,int,char) ; 
 int /*<<< orphan*/  whline (int /*<<< orphan*/ *,unsigned long,int) ; 

__attribute__((used)) static void draw_hbar(WINDOW *win, int y, int start, int len, unsigned long ptn,
		bool end)
{
	mvwaddch(win, y, start, ptn);
	whline(win, ptn, len);
	if (end)
		mvwaddch(win, y, MAX_DISP_TEMP+TDATA_LEFT, ']');
}