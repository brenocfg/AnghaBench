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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ time_t ;
struct TYPE_7__ {int persons_memory; int /*<<< orphan*/  persons; int /*<<< orphan*/  persons_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  guid; scalar_t__ usages; scalar_t__ last_t; scalar_t__ first_t; int /*<<< orphan*/  person_urls; } ;
typedef  TYPE_1__ REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  GUID_LEN ; 
 int /*<<< orphan*/  avl_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  dictionary_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mallocz (int) ; 
 int /*<<< orphan*/  person_url_compare ; 
 TYPE_3__ registry ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_generate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_unparse_lower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

REGISTRY_PERSON *registry_person_allocate(const char *person_guid, time_t when) {
    debug(D_REGISTRY, "Registry: registry_person_allocate('%s'): allocating new person, sizeof(PERSON)=%zu", (person_guid)?person_guid:"", sizeof(REGISTRY_PERSON));

    REGISTRY_PERSON *p = mallocz(sizeof(REGISTRY_PERSON));
    if(!person_guid) {
        for(;;) {
            uuid_t uuid;
            uuid_generate(uuid);
            uuid_unparse_lower(uuid, p->guid);

            debug(D_REGISTRY, "Registry: Checking if the generated person guid '%s' is unique", p->guid);
            if (!dictionary_get(registry.persons, p->guid)) {
                debug(D_REGISTRY, "Registry: generated person guid '%s' is unique", p->guid);
                break;
            }
            else
                info("Registry: generated person guid '%s' found in the registry. Retrying...", p->guid);
        }
    }
    else
        strncpyz(p->guid, person_guid, GUID_LEN);

    debug(D_REGISTRY, "Registry: registry_person_allocate('%s'): creating dictionary of urls", p->guid);
    avl_init(&p->person_urls, person_url_compare);

    p->first_t = p->last_t = (uint32_t)when;
    p->usages = 0;

    registry.persons_memory += sizeof(REGISTRY_PERSON);

    registry.persons_count++;
    dictionary_set(registry.persons, p->guid, p, sizeof(REGISTRY_PERSON));

    return p;
}