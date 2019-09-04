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
struct TYPE_2__ {int /*<<< orphan*/  vimTextArea; } ;

/* Variables and functions */
 int /*<<< orphan*/  PhInputGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PhMoveCursorAbs (int /*<<< orphan*/ ,short,short) ; 
 int /*<<< orphan*/  PtGetAbsPosition (int /*<<< orphan*/ ,short*,short*) ; 
 TYPE_1__ gui ; 

void
gui_mch_setmouse(int x, int y)
{
    short abs_x, abs_y;

    PtGetAbsPosition(gui.vimTextArea, &abs_x, &abs_y);
    /* Add the border offset? */
    PhMoveCursorAbs(PhInputGroup(NULL), abs_x + x, abs_y + y);
}