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
struct TYPE_9__ {int border_width; int char_width; int char_height; int /*<<< orphan*/  back_pixel; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int member_0; int member_1; } ;
struct TYPE_8__ {TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_3__ PhRect_t ;

/* Variables and functions */
 int Columns ; 
 int /*<<< orphan*/  DRAW_END ; 
 int /*<<< orphan*/  DRAW_START ; 
 int /*<<< orphan*/  PgDrawRect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pg_DRAW_FILL ; 
 int Rows ; 
 scalar_t__ TRUE ; 
 TYPE_4__ gui ; 
 int /*<<< orphan*/  gui_mch_set_bg_color (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ignore_draw ; 

void
gui_mch_clear_all()
{
    PhRect_t text_rect = {
	{ gui.border_width, gui.border_width },
	{ Columns * gui.char_width + gui.border_width - 1 ,
	    Rows * gui.char_height + gui.border_width - 1 }
    };

    if (is_ignore_draw == TRUE)
	return;

    DRAW_START;
    gui_mch_set_bg_color(gui.back_pixel);
    PgDrawRect(&text_rect, Pg_DRAW_FILL);
    DRAW_END;
}