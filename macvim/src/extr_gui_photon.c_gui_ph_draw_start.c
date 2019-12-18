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
struct TYPE_2__ {int /*<<< orphan*/  vimTextArea; } ;
typedef  int /*<<< orphan*/  PhGC_t ;

/* Variables and functions */
 int /*<<< orphan*/  PgClearClippingsCx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PgClearTranslationCx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PgGetGC () ; 
 int /*<<< orphan*/  PgSetRegion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgSetTranslation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pg_RELATIVE ; 
 int /*<<< orphan*/  PhTranslatePoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtFindDisjoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtWidgetOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtWidgetPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtWidgetRid (int /*<<< orphan*/ ) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_ph_raw_offset ; 

__attribute__((used)) static void
gui_ph_draw_start(void)
{
    PhGC_t *gc;

    gc = PgGetGC();
    PgSetRegion(PtWidgetRid(PtFindDisjoint(gui.vimTextArea)));
    PgClearClippingsCx(gc);
    PgClearTranslationCx(gc);

    PtWidgetOffset(gui.vimTextArea, &gui_ph_raw_offset);
    PhTranslatePoint(&gui_ph_raw_offset, PtWidgetPos(gui.vimTextArea, NULL));

    PgSetTranslation(&gui_ph_raw_offset, Pg_RELATIVE);
}