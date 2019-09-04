#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct web_client {TYPE_1__ response; } ;
struct registry_json_walk_person_urls_callback {int /*<<< orphan*/  count; TYPE_4__* m; struct web_client* w; } ;
struct TYPE_8__ {int /*<<< orphan*/  guid; } ;
struct TYPE_7__ {int /*<<< orphan*/  usages; int /*<<< orphan*/  last_t; TYPE_2__* url; } ;
struct TYPE_6__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_3__ REGISTRY_MACHINE_URL ;
typedef  TYPE_4__ REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int registry_json_machine_url_callback(void *entry, void *data) {
    REGISTRY_MACHINE_URL *mu = (REGISTRY_MACHINE_URL *)entry;
    struct registry_json_walk_person_urls_callback *c = (struct registry_json_walk_person_urls_callback *)data;
    struct web_client *w = c->w;
    REGISTRY_MACHINE *m = c->m;

    if (!strcmp(mu->url->url,"***")) return 1;

    if(unlikely(c->count++))
        buffer_strcat(w->response.data, ",");

    buffer_sprintf(w->response.data, "\n\t\t[ \"%s\", \"%s\", %u000, %u ]",
            m->guid, mu->url->url, mu->last_t, mu->usages);

    return 1;
}