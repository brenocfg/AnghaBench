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

/* Variables and functions */
 int /*<<< orphan*/  PgSetDrawMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgSetFillXORColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pg_BLACK ; 
 int /*<<< orphan*/  Pg_DRAWMODE_OPAQUE ; 
 int /*<<< orphan*/  Pg_DRAWMODE_XOR ; 
 int /*<<< orphan*/  Pg_WHITE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gui_mch_clear_all () ; 
 int /*<<< orphan*/  gui_mch_flush () ; 
 int /*<<< orphan*/  ui_delay (long,int /*<<< orphan*/ ) ; 

void
gui_mch_flash(int msec)
{
    PgSetFillXORColor(Pg_BLACK, Pg_WHITE);
    PgSetDrawMode(Pg_DRAWMODE_XOR);
    gui_mch_clear_all();
    gui_mch_flush();

    ui_delay((long) msec, TRUE);

    gui_mch_clear_all();
    PgSetDrawMode(Pg_DRAWMODE_OPAQUE);
    gui_mch_flush();
}