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
struct TYPE_9__ {int /*<<< orphan*/  back_pixel; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_3__ PhRect_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRAW_END ; 
 int /*<<< orphan*/  DRAW_START ; 
 int /*<<< orphan*/  FILL_X (int) ; 
 int /*<<< orphan*/  FILL_Y (int) ; 
 int /*<<< orphan*/  PgDrawRect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pg_DRAW_FILL ; 
 TYPE_4__ gui ; 
 int /*<<< orphan*/  gui_mch_set_bg_color (int /*<<< orphan*/ ) ; 

void
gui_mch_clear_block(int row1, int col1, int row2, int col2)
{
    PhRect_t block = {
	{ FILL_X(col1), FILL_Y(row1) },
	{ FILL_X(col2 + 1) - 1, FILL_Y(row2 + 1) - 1}
    };

    DRAW_START;
    gui_mch_set_bg_color(gui.back_pixel);
    PgDrawRect(&block, Pg_DRAW_FILL);
    DRAW_END;
}