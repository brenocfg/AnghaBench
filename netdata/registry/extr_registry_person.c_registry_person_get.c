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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  GUID_LEN ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  info (char*,char const*) ; 
 int regenerate_guid (char const*,char*) ; 
 int /*<<< orphan*/ * registry_person_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * registry_person_find (char const*) ; 
 scalar_t__ unlikely (int) ; 

REGISTRY_PERSON *registry_person_get(const char *person_guid, time_t when) {
    debug(D_REGISTRY, "Registry: registry_person_get('%s'): creating dictionary of urls", person_guid);

    REGISTRY_PERSON *p = NULL;

    if(person_guid && *person_guid) {
        char buf[GUID_LEN + 1];
        // validate it is a GUID
        if(unlikely(regenerate_guid(person_guid, buf) == -1))
            info("Registry: person guid '%s' is not a valid guid. Ignoring it.", person_guid);
        else {
            person_guid = buf;
            p = registry_person_find(person_guid);
        }
    }

    if(!p) p = registry_person_allocate(NULL, when);

    return p;
}