#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  person_urls; int /*<<< orphan*/  guid; } ;
struct TYPE_7__ {TYPE_1__* url; } ;
struct TYPE_6__ {int /*<<< orphan*/  url; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ REGISTRY_URL ;
typedef  TYPE_2__ REGISTRY_PERSON_URL ;
typedef  TYPE_3__ REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 scalar_t__ avl_search (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

inline REGISTRY_PERSON_URL *registry_person_url_index_find(REGISTRY_PERSON *p, const char *url) {
    debug(D_REGISTRY, "Registry: registry_person_url_index_find('%s', '%s')", p->guid, url);

    char buf[sizeof(REGISTRY_URL) + strlen(url)];

    REGISTRY_URL *u = (REGISTRY_URL *)&buf;
    strcpy(u->url, url);
    u->hash = simple_hash(u->url);

    REGISTRY_PERSON_URL tpu = { .url = u };

    REGISTRY_PERSON_URL *pu = (REGISTRY_PERSON_URL *)avl_search(&p->person_urls, (void *)&tpu);
    return pu;
}