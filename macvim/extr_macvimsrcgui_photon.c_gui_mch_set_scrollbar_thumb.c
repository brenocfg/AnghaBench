#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ scrollbar_T ;
typedef  int /*<<< orphan*/  PtArg_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtSetArg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtSetResources (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Pt_ARG_GAUGE_VALUE ; 
 int /*<<< orphan*/  Pt_ARG_MAXIMUM ; 
 int /*<<< orphan*/  Pt_ARG_SLIDER_SIZE ; 

void
gui_mch_set_scrollbar_thumb(scrollbar_T *sb, int val, int size, int max)
{
    int	    n = 0;
    PtArg_t args[3];

    PtSetArg(&args[ n++ ], Pt_ARG_MAXIMUM, max, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_SLIDER_SIZE, size, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_GAUGE_VALUE, val, 0);
    PtSetResources(sb->id, n, args);
}