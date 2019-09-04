#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_21__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ time_t ;
struct TYPE_28__ {int /*<<< orphan*/  guid; int /*<<< orphan*/  links; int /*<<< orphan*/  machine_urls; } ;
struct TYPE_27__ {int flags; } ;
struct TYPE_26__ {scalar_t__ last_t; int /*<<< orphan*/  guid; int /*<<< orphan*/  usages; } ;
struct TYPE_25__ {scalar_t__ last_t; int flags; int /*<<< orphan*/  machine_name; TYPE_5__* machine; int /*<<< orphan*/  usages; } ;
struct TYPE_24__ {int /*<<< orphan*/  persons_urls_count; } ;
struct TYPE_23__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ REGISTRY_URL ;
typedef  TYPE_2__ REGISTRY_PERSON_URL ;
typedef  TYPE_3__ REGISTRY_PERSON ;
typedef  TYPE_4__ REGISTRY_MACHINE_URL ;
typedef  TYPE_5__ REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int REGISTRY_URL_FLAGS_EXPIRED ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_4__* dictionary_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 TYPE_21__ registry ; 
 TYPE_2__* registry_person_url_allocate (TYPE_3__*,TYPE_5__*,TYPE_1__*,char*,size_t,scalar_t__) ; 
 TYPE_2__* registry_person_url_index_find (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* registry_person_url_reallocate (TYPE_3__*,TYPE_5__*,TYPE_1__*,char*,size_t,scalar_t__,TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

REGISTRY_PERSON_URL *registry_person_link_to_url(REGISTRY_PERSON *p, REGISTRY_MACHINE *m, REGISTRY_URL *u, char *name, size_t namelen, time_t when) {
    debug(D_REGISTRY, "registry_person_link_to_url('%s', '%s', '%s'): searching for URL in person", p->guid, m->guid, u->url);

    REGISTRY_PERSON_URL *pu = registry_person_url_index_find(p, u->url);
    if(!pu) {
        debug(D_REGISTRY, "registry_person_link_to_url('%s', '%s', '%s'): not found", p->guid, m->guid, u->url);
        pu = registry_person_url_allocate(p, m, u, name, namelen, when);
        registry.persons_urls_count++;
    }
    else {
        debug(D_REGISTRY, "registry_person_link_to_url('%s', '%s', '%s'): found", p->guid, m->guid, u->url);
        pu->usages++;
        if(likely(pu->last_t < (uint32_t)when)) pu->last_t = (uint32_t)when;

        if(pu->machine != m) {
            REGISTRY_MACHINE_URL *mu = dictionary_get(pu->machine->machine_urls, u->url);
            if(mu) {
                debug(D_REGISTRY, "registry_person_link_to_url('%s', '%s', '%s'): URL switched machines (old was '%s') - expiring it from previous machine.",
                     p->guid, m->guid, u->url, pu->machine->guid);
                mu->flags |= REGISTRY_URL_FLAGS_EXPIRED;
            }
            else {
                debug(D_REGISTRY, "registry_person_link_to_url('%s', '%s', '%s'): URL switched machines (old was '%s') - but the URL is not linked to the old machine.",
                     p->guid, m->guid, u->url, pu->machine->guid);
            }

            pu->machine->links--;
            pu->machine = m;
        }

        if(strcmp(pu->machine_name, name) != 0) {
            // the name of the PERSON_URL has changed !
            pu = registry_person_url_reallocate(p, m, u, name, namelen, when, pu);
        }
    }

    p->usages++;
    if(likely(p->last_t < (uint32_t)when)) p->last_t = (uint32_t)when;

    if(pu->flags & REGISTRY_URL_FLAGS_EXPIRED) {
        debug(D_REGISTRY, "registry_person_link_to_url('%s', '%s', '%s'): accessing an expired URL. Re-enabling URL.", p->guid, m->guid, u->url);
        pu->flags &= ~REGISTRY_URL_FLAGS_EXPIRED;
    }

    return pu;
}