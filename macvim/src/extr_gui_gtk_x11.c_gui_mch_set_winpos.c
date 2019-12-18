#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mainwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_move (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ gui ; 

void
gui_mch_set_winpos(int x, int y)
{
    gtk_window_move(GTK_WINDOW(gui.mainwin), x, y);
}