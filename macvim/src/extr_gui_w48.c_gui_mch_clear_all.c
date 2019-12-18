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
struct TYPE_5__ {int char_width; int border_width; int char_height; } ;
struct TYPE_4__ {int right; int bottom; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_1__ RECT ;

/* Variables and functions */
 int Columns ; 
 int Rows ; 
 int /*<<< orphan*/  clear_rect (TYPE_1__*) ; 
 TYPE_2__ gui ; 

void
gui_mch_clear_all(void)
{
    RECT    rc;

    rc.left = 0;
    rc.top = 0;
    rc.right = Columns * gui.char_width + 2 * gui.border_width;
    rc.bottom = Rows * gui.char_height + 2 * gui.border_width;
    clear_rect(&rc);
}