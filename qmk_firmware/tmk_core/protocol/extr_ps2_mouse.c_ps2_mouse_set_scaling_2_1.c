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
 int /*<<< orphan*/  PS2_MOUSE_SEND_SAFE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PS2_MOUSE_SET_SCALING_2_1 ; 

void ps2_mouse_set_scaling_2_1(void) { PS2_MOUSE_SEND_SAFE(PS2_MOUSE_SET_SCALING_2_1, "ps2 mouse set scaling 2:1"); }