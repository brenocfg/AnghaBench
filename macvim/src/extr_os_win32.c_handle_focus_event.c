#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bSetFocus; } ;
struct TYPE_6__ {TYPE_1__ FocusEvent; } ;
struct TYPE_7__ {TYPE_2__ Event; } ;
typedef  TYPE_3__ INPUT_RECORD ;

/* Variables and functions */
 scalar_t__ g_fJustGotFocus ; 
 int /*<<< orphan*/  ui_focus_change (int) ; 

__attribute__((used)) static void
handle_focus_event(INPUT_RECORD ir)
{
    g_fJustGotFocus = ir.Event.FocusEvent.bSetFocus;
    ui_focus_change((int)g_fJustGotFocus);
}