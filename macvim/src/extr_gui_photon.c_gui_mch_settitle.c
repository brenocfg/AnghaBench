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
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_6__ {TYPE_1__* w_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  vimWindow; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_fnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_WINDOW_TITLE ; 
 TYPE_3__* curwin ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_ph_pg_set_buffer_num (int /*<<< orphan*/ ) ; 

void
gui_mch_settitle(char_u *title,	char_u *icon)
{
#ifdef USE_PANEL_GROUP
    gui_ph_pg_set_buffer_num(curwin->w_buffer->b_fnum);
#endif
    PtSetResource(gui.vimWindow, Pt_ARG_WINDOW_TITLE, title, 0);
    /* Not sure what to do with the icon text, set balloon text somehow? */
}