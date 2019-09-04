#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ time_t ;
struct TYPE_7__ {int machines_memory; int /*<<< orphan*/  machines; int /*<<< orphan*/  machines_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  guid; scalar_t__ usages; scalar_t__ last_t; scalar_t__ first_t; int /*<<< orphan*/  machine_urls; } ;
typedef  TYPE_1__ REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  DICTIONARY_FLAGS ; 
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  GUID_LEN ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  dictionary_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 TYPE_1__* mallocz (int) ; 
 TYPE_3__ registry ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

REGISTRY_MACHINE *registry_machine_allocate(const char *machine_guid, time_t when) {
    debug(D_REGISTRY, "Registry: registry_machine_allocate('%s'): creating new machine, sizeof(MACHINE)=%zu", machine_guid, sizeof(REGISTRY_MACHINE));

    REGISTRY_MACHINE *m = mallocz(sizeof(REGISTRY_MACHINE));

    strncpyz(m->guid, machine_guid, GUID_LEN);

    debug(D_REGISTRY, "Registry: registry_machine_allocate('%s'): creating dictionary of urls", machine_guid);
    m->machine_urls = dictionary_create(DICTIONARY_FLAGS);

    m->first_t = m->last_t = (uint32_t)when;
    m->usages = 0;

    registry.machines_memory += sizeof(REGISTRY_MACHINE);

    registry.machines_count++;
    dictionary_set(registry.machines, m->guid, m, sizeof(REGISTRY_MACHINE));

    return m;
}