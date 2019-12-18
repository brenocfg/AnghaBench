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
struct TYPE_2__ {int /*<<< orphan*/  back_pixel; } ;

/* Variables and functions */
 int /*<<< orphan*/  XmChangeColor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmNbackground ; 
 int /*<<< orphan*/  XtVaSetValues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/ * textArea ; 

void
gui_x11_set_back_color()
{
    if (textArea != NULL)
#if (XmVersion >= 1002)
	XmChangeColor(textArea, gui.back_pixel);
#else
	XtVaSetValues(textArea,
		  XmNbackground, gui.back_pixel,
		  NULL);
#endif
}