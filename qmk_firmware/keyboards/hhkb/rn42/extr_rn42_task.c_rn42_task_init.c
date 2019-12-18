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
struct TYPE_2__ {int /*<<< orphan*/  nkro; } ;

/* Variables and functions */
 int /*<<< orphan*/  battery_init () ; 
 TYPE_1__ keymap_config ; 
 int /*<<< orphan*/  rn42_nkro_last ; 

void rn42_task_init(void)
{
    battery_init();
#ifdef NKRO_ENABLE
    rn42_nkro_last = keymap_config.nkro;
#endif
}