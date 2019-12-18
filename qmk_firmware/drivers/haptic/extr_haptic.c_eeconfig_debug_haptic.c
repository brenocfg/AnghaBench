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
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,...) ; 
 TYPE_1__ haptic_config ; 

void eeconfig_debug_haptic(void) {
    dprintf("haptic_config eprom\n");
    dprintf("haptic_config.enable = %d\n", haptic_config.enable);
    dprintf("haptic_config.mode = %d\n", haptic_config.mode);
}