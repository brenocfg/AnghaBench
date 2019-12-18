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
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {int x; int y; } ;
struct TYPE_7__ {TYPE_2__ ul; TYPE_1__ lr; } ;
typedef  TYPE_3__ PhRect_t ;

/* Variables and functions */
 int /*<<< orphan*/  PhInputGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PhWindowQueryVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  Ph_QUERY_WORKSPACE ; 

void
gui_mch_get_screen_dimensions(int *screen_w, int *screen_h)
{
    PhRect_t console;

    PhWindowQueryVisible(Ph_QUERY_WORKSPACE, 0,
	    PhInputGroup(NULL), &console);

    *screen_w = console.lr.x - console.ul.x + 1;
    *screen_h = console.lr.y - console.ul.y + 1;
}