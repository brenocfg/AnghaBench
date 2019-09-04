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
struct TYPE_5__ {int num_cols; int char_width; int num_rows; int char_height; } ;
struct TYPE_4__ {int right; int bottom; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_1__ Rect ;

/* Variables and functions */
 int /*<<< orphan*/  InvertRect (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  ui_delay (long,int /*<<< orphan*/ ) ; 

void
gui_mch_flash(int msec)
{
    /* Do a visual beep by reversing the foreground and background colors */
    Rect    rc;

    /*
     * Note: InvertRect() excludes right and bottom of rectangle.
     */
    rc.left = 0;
    rc.top = 0;
    rc.right = gui.num_cols * gui.char_width;
    rc.bottom = gui.num_rows * gui.char_height;
    InvertRect(&rc);

    ui_delay((long)msec, TRUE);		/* wait for some msec */

    InvertRect(&rc);
}