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

/* Variables and functions */
 int /*<<< orphan*/  PS2_MOUSE_REMOTE_MODE ; 
 int /*<<< orphan*/  PS2_MOUSE_SEND_SAFE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PS2_MOUSE_SET_REMOTE_MODE ; 
 int /*<<< orphan*/  ps2_mouse_mode ; 

void ps2_mouse_set_remote_mode(void) {
    PS2_MOUSE_SEND_SAFE(PS2_MOUSE_SET_REMOTE_MODE, "ps2 mouse set remote mode");
    ps2_mouse_mode = PS2_MOUSE_REMOTE_MODE;
}