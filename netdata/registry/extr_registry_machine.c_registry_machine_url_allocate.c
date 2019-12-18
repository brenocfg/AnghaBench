#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ time_t ;
struct TYPE_14__ {int machines_urls_memory; } ;
struct TYPE_13__ {int /*<<< orphan*/  machine_urls; int /*<<< orphan*/  guid; } ;
struct TYPE_12__ {int usages; int /*<<< orphan*/  flags; TYPE_1__* url; scalar_t__ last_t; scalar_t__ first_t; } ;
struct TYPE_11__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ REGISTRY_URL ;
typedef  TYPE_2__ REGISTRY_MACHINE_URL ;
typedef  TYPE_3__ REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  REGISTRY_URL_FLAGS_DEFAULT ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dictionary_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__* mallocz (int) ; 
 TYPE_8__ registry ; 
 int /*<<< orphan*/  registry_url_link (TYPE_1__*) ; 

REGISTRY_MACHINE_URL *registry_machine_url_allocate(REGISTRY_MACHINE *m, REGISTRY_URL *u, time_t when) {
    debug(D_REGISTRY, "registry_machine_url_allocate('%s', '%s'): allocating %zu bytes", m->guid, u->url, sizeof(REGISTRY_MACHINE_URL));

    REGISTRY_MACHINE_URL *mu = mallocz(sizeof(REGISTRY_MACHINE_URL));

    mu->first_t = mu->last_t = (uint32_t)when;
    mu->usages = 1;
    mu->url = u;
    mu->flags = REGISTRY_URL_FLAGS_DEFAULT;

    registry.machines_urls_memory += sizeof(REGISTRY_MACHINE_URL);

    debug(D_REGISTRY, "registry_machine_url_allocate('%s', '%s'): indexing URL in machine", m->guid, u->url);
    dictionary_set(m->machine_urls, u->url, mu, sizeof(REGISTRY_MACHINE_URL));

    registry_url_link(u);

    return mu;
}