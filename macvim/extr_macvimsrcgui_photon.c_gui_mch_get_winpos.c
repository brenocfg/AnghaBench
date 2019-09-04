#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vimWindow; } ;
struct TYPE_4__ {int x; int y; } ;
typedef  TYPE_1__ PhPoint_t ;

/* Variables and functions */
 int OK ; 
 TYPE_1__* PtWidgetPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ gui ; 

int
gui_mch_get_winpos(int *x, int *y)
{
    PhPoint_t *pos;

    pos = PtWidgetPos(gui.vimWindow, NULL);

    *x = pos->x;
    *y = pos->y;

    return OK;
}