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
struct TYPE_4__ {int /*<<< orphan*/  gtk_sel_atom; } ;
typedef  TYPE_1__ VimClipboard ;
struct TYPE_5__ {int /*<<< orphan*/  event_time; int /*<<< orphan*/  drawarea; } ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int gtk_selection_owner_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_mch_update () ; 

int
clip_mch_own_selection(VimClipboard *cbd)
{
    int success;

    success = gtk_selection_owner_set(gui.drawarea, cbd->gtk_sel_atom,
				      gui.event_time);
    gui_mch_update();
    return (success) ? OK : FAIL;
}