#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vimmenu_T ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  int /*<<< orphan*/  PtCallbackInfo_t ;

/* Variables and functions */
 int Pt_CONTINUE ; 
 int /*<<< orphan*/  gui_menu_cb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gui_ph_handle_menu(PtWidget_t *widget, void *data, PtCallbackInfo_t *info)
{
    if (data != NULL)
    {
	vimmenu_T *menu = (vimmenu_T *) data;
	gui_menu_cb(menu);
    }
    return Pt_CONTINUE;
}