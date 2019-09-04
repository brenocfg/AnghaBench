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
struct winsize {int ws_row; int ws_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCGWINSZ ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  tty_in ; 

void terminal_get_size(int *w, int *h)
{
    struct winsize ws;
    if (ioctl(tty_in, TIOCGWINSZ, &ws) < 0 || !ws.ws_row || !ws.ws_col)
        return;

    *w = ws.ws_col;
    *h = ws.ws_row;
}