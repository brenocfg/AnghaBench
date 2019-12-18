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
struct TYPE_2__ {int /*<<< orphan*/  machines; } ;
typedef  int /*<<< orphan*/  REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * dictionary_get (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__ registry ; 

REGISTRY_MACHINE *registry_machine_find(const char *machine_guid) {
    debug(D_REGISTRY, "Registry: registry_machine_find('%s')", machine_guid);
    return dictionary_get(registry.machines, machine_guid);
}