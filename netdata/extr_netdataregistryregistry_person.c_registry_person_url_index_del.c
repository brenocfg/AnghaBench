#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avl ;
struct TYPE_9__ {int /*<<< orphan*/  guid; int /*<<< orphan*/  person_urls; } ;
struct TYPE_8__ {TYPE_1__* url; } ;
struct TYPE_7__ {char* url; } ;
typedef  TYPE_2__ REGISTRY_PERSON_URL ;
typedef  TYPE_3__ REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 scalar_t__ avl_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,...) ; 

inline REGISTRY_PERSON_URL *registry_person_url_index_del(REGISTRY_PERSON *p, REGISTRY_PERSON_URL *pu) {
    debug(D_REGISTRY, "Registry: registry_person_url_index_del('%s', '%s')", p->guid, pu->url->url);
    REGISTRY_PERSON_URL *tpu = (REGISTRY_PERSON_URL *)avl_remove(&(p->person_urls), (avl *)(pu));
    if(!tpu)
        error("Registry: registry_person_url_index_del('%s', '%s') deleted nothing", p->guid, pu->url->url);
    else if(tpu != pu)
        error("Registry: registry_person_url_index_del('%s', '%s') deleted wrong URL '%s'", p->guid, pu->url->url, tpu->url->url);

    return tpu;
}