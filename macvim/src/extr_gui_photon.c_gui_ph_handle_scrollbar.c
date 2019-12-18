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
typedef  int /*<<< orphan*/  scrollbar_T ;
struct TYPE_5__ {TYPE_1__* cbdata; } ;
struct TYPE_4__ {int position; int action; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  TYPE_1__ PtScrollbarCallback_t ;
typedef  TYPE_2__ PtCallbackInfo_t ;

/* Variables and functions */
 int FALSE ; 
 int Pt_CONTINUE ; 
#define  Pt_SCROLL_DRAGGED 129 
#define  Pt_SCROLL_SET 128 
 int TRUE ; 
 int /*<<< orphan*/  gui_drag_scrollbar (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
gui_ph_handle_scrollbar(PtWidget_t *widget, void *data, PtCallbackInfo_t *info)
{
    PtScrollbarCallback_t *scroll;
    scrollbar_T *sb;
    int	    value, dragging = FALSE;

    scroll = info->cbdata;

    sb = (scrollbar_T *) data;
    if (sb != NULL)
    {
	value = scroll->position;
	switch (scroll->action)
	{
	    case Pt_SCROLL_DRAGGED:
		dragging = TRUE;
		break;

	    case Pt_SCROLL_SET:
		/* FIXME: return straight away here? */
		return Pt_CONTINUE;
		break;
	}

	gui_drag_scrollbar(sb, value, dragging);
    }
    return Pt_CONTINUE;
}