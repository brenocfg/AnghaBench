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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {int /*<<< orphan*/  usages_count; } ;
typedef  int /*<<< orphan*/  REGISTRY_URL ;
typedef  int /*<<< orphan*/  REGISTRY_PERSON ;
typedef  int /*<<< orphan*/  REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 TYPE_1__ registry ; 
 char* registry_fix_machine_name (char*,size_t*) ; 
 char* registry_fix_url (char*,size_t*) ; 
 int /*<<< orphan*/  registry_log (char,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * registry_machine_get (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_machine_link_to_url (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * registry_person_get (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_person_link_to_url (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * registry_url_get (char*,size_t) ; 

REGISTRY_PERSON *registry_request_access(char *person_guid, char *machine_guid, char *url, char *name, time_t when) {
    debug(D_REGISTRY, "registry_request_access('%s', '%s', '%s'): NEW REQUEST", (person_guid)?person_guid:"", machine_guid, url);

    REGISTRY_MACHINE *m = registry_machine_get(machine_guid, when);
    if(!m) return NULL;

    // make sure the name is valid
    size_t namelen;
    name = registry_fix_machine_name(name, &namelen);

    size_t urllen;
    url = registry_fix_url(url, &urllen);

    REGISTRY_PERSON *p = registry_person_get(person_guid, when);

    REGISTRY_URL *u = registry_url_get(url, urllen);
    registry_person_link_to_url(p, m, u, name, namelen, when);
    registry_machine_link_to_url(m, u, when);

    registry_log('A', p, m, u, name);

    registry.usages_count++;

    return p;
}