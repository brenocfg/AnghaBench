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
struct vo {int /*<<< orphan*/  x11; } ;
struct TYPE_3__ {long all_event_masks; long your_event_mask; } ;
typedef  TYPE_1__ XWindowAttributes ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 long ButtonPressMask ; 
 long ButtonReleaseMask ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ ,char*) ; 
 long NoEventMask ; 
 long PointerMotionMask ; 
 scalar_t__ XGetWindowAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XSelectInput (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void vo_x11_selectinput_witherr(struct vo *vo,
                                       Display *display,
                                       Window w,
                                       long event_mask)
{
    XSelectInput(display, w, NoEventMask);

    // NOTE: this can raise BadAccess, which should be ignored by the X error
    //       handler; also see below
    XSelectInput(display, w, event_mask);

    // Test whether setting the event mask failed (with a BadAccess X error,
    // although we don't know whether this really happened).
    // This is needed for obscure situations like using --rootwin with a window
    // manager active.
    XWindowAttributes a;
    if (XGetWindowAttributes(display, w, &a)) {
        long bad = ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
        if ((event_mask & bad) && (a.all_event_masks & bad) &&
            ((a.your_event_mask & bad) != (event_mask & bad)))
        {
            MP_ERR(vo->x11, "X11 error: error during XSelectInput "
                   "call, trying without mouse events\n");
            XSelectInput(display, w, event_mask & ~bad);
        }
    }
}