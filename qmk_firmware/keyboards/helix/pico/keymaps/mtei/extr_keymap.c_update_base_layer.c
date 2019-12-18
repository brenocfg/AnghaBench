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
 int current_default_layer ; 
 int /*<<< orphan*/  default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  eeconfig_update_default_layer (unsigned long) ; 

void update_base_layer(int base)
{
    if( current_default_layer != base ) {
        eeconfig_update_default_layer(1UL<<base);
        default_layer_set(1UL<<base);
    }
}