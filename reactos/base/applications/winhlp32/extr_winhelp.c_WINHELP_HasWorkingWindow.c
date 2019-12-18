#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* active_win; TYPE_2__* win_list; } ;
struct TYPE_5__ {TYPE_1__* page; scalar_t__ next; } ;
struct TYPE_4__ {int /*<<< orphan*/ * file; } ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 TYPE_3__ Globals ; 
 int TRUE ; 

__attribute__((used)) static BOOL WINHELP_HasWorkingWindow(void)
{
    if (!Globals.active_win) return FALSE;
    if (Globals.active_win->next || Globals.win_list != Globals.active_win) return TRUE;
    return Globals.active_win->page != NULL && Globals.active_win->page->file != NULL;
}