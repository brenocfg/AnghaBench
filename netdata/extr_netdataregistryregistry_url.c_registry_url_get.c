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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  avl ;
struct TYPE_9__ {size_t max_url_length; int urls_memory; int /*<<< orphan*/  urls_count; int /*<<< orphan*/  registry_urls_root_index; } ;
struct TYPE_8__ {char* url; void* hash; scalar_t__ links; void* len; } ;
typedef  TYPE_1__ REGISTRY_URL ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 scalar_t__ avl_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 TYPE_5__ registry ; 
 TYPE_1__* registry_url_index_add (TYPE_1__*) ; 
 void* simple_hash (char*) ; 
 int /*<<< orphan*/  strncpyz (char*,char const*,void*) ; 

REGISTRY_URL *registry_url_get(const char *url, size_t urllen) {
    // protection from too big URLs
    if(urllen > registry.max_url_length)
        urllen = registry.max_url_length;

    debug(D_REGISTRY, "Registry: registry_url_get('%s', %zu)", url, urllen);

    char buf[sizeof(REGISTRY_URL) + urllen]; // no need for +1, 1 is already in REGISTRY_URL
    REGISTRY_URL *n = (REGISTRY_URL *)&buf[0];
    n->len = (uint16_t)urllen;
    strncpyz(n->url, url, n->len);
    n->hash = simple_hash(n->url);

    REGISTRY_URL *u = (REGISTRY_URL *)avl_search(&(registry.registry_urls_root_index), (avl *)n);
    if(!u) {
        debug(D_REGISTRY, "Registry: registry_url_get('%s', %zu): allocating %zu bytes", url, urllen, sizeof(REGISTRY_URL) + urllen);
        u = callocz(1, sizeof(REGISTRY_URL) + urllen); // no need for +1, 1 is already in REGISTRY_URL

        // a simple strcpy() should do the job
        // but I prefer to be safe, since the caller specified urllen
        u->len = (uint16_t)urllen;
        strncpyz(u->url, url, u->len);
        u->links = 0;
        u->hash = simple_hash(u->url);

        registry.urls_memory += sizeof(REGISTRY_URL) + urllen; // no need for +1, 1 is already in REGISTRY_URL

        debug(D_REGISTRY, "Registry: registry_url_get('%s'): indexing it", url);
        n = registry_url_index_add(u);
        if(n != u) {
            error("INTERNAL ERROR: registry_url_get(): url '%s' already exists in the registry as '%s'", u->url, n->url);
            freez(u);
            u = n;
        }
        else
            registry.urls_count++;
    }

    return u;
}