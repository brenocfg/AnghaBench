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
 int /*<<< orphan*/  led_init_ports () ; 
 int /*<<< orphan*/  led_set_layer (int /*<<< orphan*/ ) ; 

void matrix_init_user(void)
{
    led_init_ports();

    led_set_layer(0);

    /*KNOPS_INIT*/
}