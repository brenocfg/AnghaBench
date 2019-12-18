#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* model; TYPE_3__* view; } ;
struct TYPE_7__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {TYPE_2__ pos; } ;
struct TYPE_6__ {char* title; } ;
typedef  TYPE_4__ RPanel ;
typedef  int /*<<< orphan*/  RConsCanvas ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_canvas_gotoxy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  r_cons_canvas_write (int /*<<< orphan*/ *,char*) ; 
 char* r_str_ansi_crop (char*,int,int,int,int) ; 

void __menu_panel_print(RConsCanvas *can, RPanel *panel, int x, int y, int w, int h) {
	(void) r_cons_canvas_gotoxy (can, panel->view->pos.x + 2, panel->view->pos.y + 2);
	char *text = r_str_ansi_crop (panel->model->title, x, y, w, h);
	if (text) {
		r_cons_canvas_write (can, text);
		free (text);
	} else {
		r_cons_canvas_write (can, panel->model->title);
	}
}