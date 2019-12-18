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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_update_haptic (int /*<<< orphan*/ ) ; 
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void haptic_set_mode(uint8_t mode) {
    haptic_config.mode = mode;
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.mode = %u\n", haptic_config.mode);
}