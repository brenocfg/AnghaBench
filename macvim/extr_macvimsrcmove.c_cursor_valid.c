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
struct TYPE_3__ {int w_valid; } ;

/* Variables and functions */
 int VALID_WCOL ; 
 int VALID_WROW ; 
 int /*<<< orphan*/  check_cursor_moved (TYPE_1__*) ; 
 TYPE_1__* curwin ; 

int
cursor_valid()
{
    check_cursor_moved(curwin);
    return ((curwin->w_valid & (VALID_WROW|VALID_WCOL)) ==
						      (VALID_WROW|VALID_WCOL));
}