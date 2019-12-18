#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vimTextArea; } ;
struct TYPE_7__ {int member_0; int member_1; } ;
struct TYPE_6__ {int member_0; int member_1; } ;
struct TYPE_8__ {TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_3__ PhArea_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_AREA ; 
 TYPE_4__ gui ; 

void
gui_mch_set_text_area_pos(int x, int y, int w, int h)
{
    PhArea_t area = {{x, y}, {w, h}};

    PtSetResource(gui.vimTextArea, Pt_ARG_AREA, &area, 0);
}