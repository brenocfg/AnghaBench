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
 int /*<<< orphan*/  PS2_MOUSE_DISABLE_DATA_REPORTING ; 
 int /*<<< orphan*/  PS2_MOUSE_SEND (int /*<<< orphan*/ ,char*) ; 

void ps2_mouse_disable_data_reporting(void) { PS2_MOUSE_SEND(PS2_MOUSE_DISABLE_DATA_REPORTING, "ps2 mouse disable data reporting"); }