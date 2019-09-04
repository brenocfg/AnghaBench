#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  persons; } ;
struct TYPE_7__ {scalar_t__ root; } ;
struct TYPE_8__ {int /*<<< orphan*/  guid; TYPE_1__ person_urls; } ;
typedef  int /*<<< orphan*/  REGISTRY_PERSON_URL ;
typedef  TYPE_2__ REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freez (TYPE_2__*) ; 
 TYPE_5__ registry ; 
 int /*<<< orphan*/  registry_person_unlink_from_url (TYPE_2__*,int /*<<< orphan*/ *) ; 

void registry_person_del(REGISTRY_PERSON *p) {
    debug(D_REGISTRY, "Registry: registry_person_del('%s'): creating dictionary of urls", p->guid);

    while(p->person_urls.root)
        registry_person_unlink_from_url(p, (REGISTRY_PERSON_URL *)p->person_urls.root);

    debug(D_REGISTRY, "Registry: deleting person '%s' from persons registry", p->guid);
    dictionary_del(registry.persons, p->guid);

    debug(D_REGISTRY, "Registry: freeing person '%s'", p->guid);
    freez(p);
}