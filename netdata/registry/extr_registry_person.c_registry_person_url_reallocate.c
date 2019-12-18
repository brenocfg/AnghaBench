#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_19__ {int /*<<< orphan*/  guid; } ;
struct TYPE_18__ {int /*<<< orphan*/  guid; } ;
struct TYPE_17__ {char* machine_name; int /*<<< orphan*/  flags; int /*<<< orphan*/  usages; int /*<<< orphan*/  last_t; int /*<<< orphan*/  first_t; int /*<<< orphan*/  machine; } ;
struct TYPE_16__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ REGISTRY_URL ;
typedef  TYPE_2__ REGISTRY_PERSON_URL ;
typedef  TYPE_3__ REGISTRY_PERSON ;
typedef  TYPE_4__ REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* registry_person_url_allocate (TYPE_3__*,TYPE_4__*,TYPE_1__*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_person_url_free (TYPE_3__*,TYPE_2__*) ; 

REGISTRY_PERSON_URL *registry_person_url_reallocate(REGISTRY_PERSON *p, REGISTRY_MACHINE *m, REGISTRY_URL *u, char *name, size_t namelen, time_t when, REGISTRY_PERSON_URL *pu) {
    debug(D_REGISTRY, "registry_person_url_reallocate('%s', '%s', '%s'): allocating %zu bytes", p->guid, m->guid, u->url, sizeof(REGISTRY_PERSON_URL) + namelen);

    // keep a backup
    REGISTRY_PERSON_URL pu2 = {
            .first_t = pu->first_t,
            .last_t = pu->last_t,
            .usages = pu->usages,
            .flags = pu->flags,
            .machine = pu->machine,
            .machine_name = ""
    };

    // remove the existing one from the index
    registry_person_url_free(p, pu);
    pu = &pu2;

    // allocate a new one
    REGISTRY_PERSON_URL *tpu = registry_person_url_allocate(p, m, u, name, namelen, when);
    tpu->first_t = pu->first_t;
    tpu->last_t = pu->last_t;
    tpu->usages = pu->usages;
    tpu->flags = pu->flags;

    return tpu;
}