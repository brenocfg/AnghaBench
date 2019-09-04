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
typedef  int /*<<< orphan*/  guint32 ;
struct TYPE_2__ {scalar_t__ in_focus; } ;
typedef  int /*<<< orphan*/  GtkFunction ;

/* Variables and functions */
 int /*<<< orphan*/  BLINK_ON ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ blink_cb ; 
 scalar_t__ blink_offtime ; 
 scalar_t__ blink_ontime ; 
 int /*<<< orphan*/  blink_state ; 
 scalar_t__ blink_timer ; 
 scalar_t__ blink_waittime ; 
 scalar_t__ gtk_timeout_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_timeout_remove (scalar_t__) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_update_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_start_blink(void)
{
    if (blink_timer)
    {
	gtk_timeout_remove(blink_timer);
	blink_timer = 0;
    }
    /* Only switch blinking on if none of the times is zero */
    if (blink_waittime && blink_ontime && blink_offtime && gui.in_focus)
    {
	blink_timer = gtk_timeout_add((guint32)blink_waittime,
				   (GtkFunction) blink_cb, NULL);
	blink_state = BLINK_ON;
	gui_update_cursor(TRUE, FALSE);
    }
}