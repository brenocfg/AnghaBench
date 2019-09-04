#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** strings; } ;
typedef  TYPE_1__ vimmenu_T ;
typedef  char char_u ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  int /*<<< orphan*/  PtArg_t ;
typedef  int /*<<< orphan*/  PgColor_t ;

/* Variables and functions */
 int MENU_INDEX_TIP ; 
 int /*<<< orphan*/  PtGetResources (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PtInflateBalloon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtSetArg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_POINTER ; 
 int /*<<< orphan*/  Pt_BALLOON_TOP ; 

__attribute__((used)) static PtWidget_t * gui_ph_show_tooltip(PtWidget_t *window,
			     PtWidget_t *widget,
			     int position,
			     char *text,
			     char *font,
			     PgColor_t fill_color,
			     PgColor_t text_color)
{
    PtArg_t arg;
    vimmenu_T *menu;
    char_u  *tooltip;

    PtSetArg(&arg, Pt_ARG_POINTER, &menu, 0);
    PtGetResources(widget, 1, &arg);

    /* Override the text and position */

    tooltip = text;
    if (menu != NULL)
    {
	int index = MENU_INDEX_TIP;
	if (menu->strings[ index ] != NULL)
	    tooltip = menu->strings[ index ];
    }

    return PtInflateBalloon(
	    window,
	    widget,
	    /* Don't put the balloon at the bottom,
	     * it gets drawn over by gfx done in the PtRaw */
	    Pt_BALLOON_TOP,
	    tooltip,
	    font,
	    fill_color,
	    text_color);
}