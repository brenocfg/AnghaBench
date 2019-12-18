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
 int /*<<< orphan*/  CONFIG_SECTION_HEALTH ; 
 int /*<<< orphan*/  D_HEALTH ; 
 scalar_t__ config_get_boolean (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 unsigned int default_health_enabled ; 
 int /*<<< orphan*/  health_silencers_init () ; 

void health_init(void) {
    debug(D_HEALTH, "Health configuration initializing");

    if(!(default_health_enabled = (unsigned int)config_get_boolean(CONFIG_SECTION_HEALTH, "enabled", default_health_enabled))) {
        debug(D_HEALTH, "Health is disabled.");
        return;
    }

    health_silencers_init();
}