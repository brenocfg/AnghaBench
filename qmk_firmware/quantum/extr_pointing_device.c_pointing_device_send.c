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
struct TYPE_3__ {scalar_t__ h; scalar_t__ v; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  host_mouse_send (TYPE_1__*) ; 
 TYPE_1__ mouseReport ; 

__attribute__((weak)) void pointing_device_send(void) {
    // If you need to do other things, like debugging, this is the place to do it.
    host_mouse_send(&mouseReport);
    // send it and 0 it out except for buttons, so those stay until they are explicity over-ridden using update_pointing_device
    mouseReport.x = 0;
    mouseReport.y = 0;
    mouseReport.v = 0;
    mouseReport.h = 0;
}