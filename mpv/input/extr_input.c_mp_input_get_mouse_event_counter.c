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
struct input_ctx {int mouse_event_counter; int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 scalar_t__ mp_input_test_mouse_active (struct input_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int mp_input_get_mouse_event_counter(struct input_ctx *ictx)
{
    // Make the frontend always display the mouse cursor (as long as it's not
    // forced invisible) if mouse input is desired.
    input_lock(ictx);
    if (mp_input_test_mouse_active(ictx, ictx->mouse_x, ictx->mouse_y))
        ictx->mouse_event_counter++;
    int ret = ictx->mouse_event_counter;
    input_unlock(ictx);
    return ret;
}