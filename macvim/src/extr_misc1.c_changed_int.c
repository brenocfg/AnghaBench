#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* b_changed; } ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  check_status (TYPE_1__*) ; 
 TYPE_1__* curbuf ; 
 int /*<<< orphan*/  ml_setflags (TYPE_1__*) ; 
 void* need_maketitle ; 
 void* redraw_tabline ; 

void
changed_int()
{
    curbuf->b_changed = TRUE;
    ml_setflags(curbuf);
#ifdef FEAT_WINDOWS
    check_status(curbuf);
    redraw_tabline = TRUE;
#endif
#ifdef FEAT_TITLE
    need_maketitle = TRUE;	    /* set window title later */
#endif
}