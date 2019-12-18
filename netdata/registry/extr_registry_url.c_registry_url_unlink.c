#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  urls_memory; } ;
struct TYPE_7__ {char* url; int /*<<< orphan*/  links; scalar_t__ len; } ;
typedef  TYPE_1__ REGISTRY_URL ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 TYPE_5__ registry ; 
 TYPE_1__* registry_url_index_del (TYPE_1__*) ; 

void registry_url_unlink(REGISTRY_URL *u) {
    u->links--;
    if(!u->links) {
        debug(D_REGISTRY, "Registry: registry_url_unlink('%s'): No more links for this URL", u->url);
        REGISTRY_URL *n = registry_url_index_del(u);
        if(!n) {
            error("INTERNAL ERROR: registry_url_unlink('%s'): cannot find url in index", u->url);
        }
        else {
            if(n != u) {
                error("INTERNAL ERROR: registry_url_unlink('%s'): deleted different url '%s'", u->url, n->url);
            }

            registry.urls_memory -= sizeof(REGISTRY_URL) + n->len; // no need for +1, 1 is already in REGISTRY_URL
            freez(n);
        }
    }
    else
        debug(D_REGISTRY, "Registry: registry_url_unlink('%s'): URL has %u links left", u->url, u->links);
}