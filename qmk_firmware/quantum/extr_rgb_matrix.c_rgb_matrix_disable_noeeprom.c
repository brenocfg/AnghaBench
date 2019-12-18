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
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  STARTING ; 
 TYPE_1__ rgb_matrix_config ; 
 int /*<<< orphan*/  rgb_task_state ; 

void rgb_matrix_disable_noeeprom(void) {
    if (rgb_matrix_config.enable) rgb_task_state = STARTING;
    rgb_matrix_config.enable = 0;
}