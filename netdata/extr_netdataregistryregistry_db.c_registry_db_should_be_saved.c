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
struct TYPE_2__ {scalar_t__ log_count; scalar_t__ save_registry_every_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 TYPE_1__ registry ; 

int registry_db_should_be_saved(void) {
    debug(D_REGISTRY, "log entries %llu, max %llu", registry.log_count, registry.save_registry_every_entries);
    return registry.log_count > registry.save_registry_every_entries;
}