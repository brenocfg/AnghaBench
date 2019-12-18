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
struct TYPE_2__ {int /*<<< orphan*/  vimWindow; int /*<<< orphan*/  back_pixel; int /*<<< orphan*/  def_back_pixel; int /*<<< orphan*/  norm_pixel; int /*<<< orphan*/  def_norm_pixel; } ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int /*<<< orphan*/  Pg_BLACK ; 
 int /*<<< orphan*/  Pg_WHITE ; 
 scalar_t__ PtRealizeWidget (int /*<<< orphan*/ ) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_check_colors () ; 
 int /*<<< orphan*/  gui_mch_set_winpos (int,int) ; 
 int gui_win_x ; 
 int gui_win_y ; 
 int /*<<< orphan*/  highlight_gui_started () ; 
 int /*<<< orphan*/  set_normal_colors () ; 

int
gui_mch_open(void)
{
    gui.norm_pixel =  Pg_BLACK;
    gui.back_pixel =  Pg_WHITE;

    set_normal_colors();

    gui_check_colors();
    gui.def_norm_pixel = gui.norm_pixel;
    gui.def_back_pixel = gui.back_pixel;

    highlight_gui_started();

    if (gui_win_x != -1 && gui_win_y != -1)
	gui_mch_set_winpos(gui_win_x, gui_win_y);

    return (PtRealizeWidget(gui.vimWindow) == 0) ? OK : FAIL;
}