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
typedef  int /*<<< orphan*/  guicolor_T ;
struct TYPE_9__ {scalar_t__ char_height; int /*<<< orphan*/  row; int /*<<< orphan*/  col; } ;
struct TYPE_7__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {TYPE_2__ ul; TYPE_1__ lr; } ;
typedef  TYPE_3__ PhRect_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRAW_END ; 
 int /*<<< orphan*/  DRAW_START ; 
 scalar_t__ FILL_X (int /*<<< orphan*/ ) ; 
 scalar_t__ FILL_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgDrawRect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pg_DRAW_FILL ; 
 TYPE_4__ gui ; 
 int /*<<< orphan*/  gui_mch_set_bg_color (int /*<<< orphan*/ ) ; 

void
gui_mch_draw_part_cursor(int w, int h, guicolor_T color)
{
    PhRect_t r;

    r.ul.x = FILL_X(gui.col);
    r.ul.y = FILL_Y(gui.row) + gui.char_height - h;
    r.lr.x = r.ul.x + w - 1;
    r.lr.y = r.ul.y + h - 1;

    DRAW_START;
    gui_mch_set_bg_color(color);
    PgDrawRect(&r, Pg_DRAW_FILL);
    DRAW_END;
}