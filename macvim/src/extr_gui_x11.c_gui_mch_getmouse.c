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
typedef  int /*<<< orphan*/  Window ;
struct TYPE_2__ {scalar_t__ wid; int /*<<< orphan*/  dpy; } ;

/* Variables and functions */
 scalar_t__ XQueryPointer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,unsigned int*) ; 
 TYPE_1__ gui ; 

void
gui_mch_getmouse(int *x, int *y)
{
    int		rootx, rooty, winx, winy;
    Window	root, child;
    unsigned int mask;

    if (gui.wid && XQueryPointer(gui.dpy, gui.wid, &root, &child,
					 &rootx, &rooty, &winx, &winy, &mask)) {
	*x = winx;
	*y = winy;
    } else {
	*x = -1;
	*y = -1;
    }
}