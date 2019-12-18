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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct web_client {TYPE_1__ response; } ;
struct registry_person_url_callback_verify_machine_exists_data {scalar_t__ count; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_7__ {int /*<<< orphan*/  guid; int /*<<< orphan*/  person_urls; } ;
typedef  int /*<<< orphan*/  RRDHOST ;
typedef  TYPE_2__ REGISTRY_PERSON ;
typedef  int /*<<< orphan*/  REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTRY_STATUS_FAILED ; 
 int /*<<< orphan*/  REGISTRY_STATUS_OK ; 
 int /*<<< orphan*/  avl_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct registry_person_url_callback_verify_machine_exists_data*) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ registry ; 
 int registry_json_disabled (int /*<<< orphan*/ *,struct web_client*,char*) ; 
 int /*<<< orphan*/  registry_json_footer (struct web_client*) ; 
 int /*<<< orphan*/  registry_json_header (int /*<<< orphan*/ *,struct web_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_lock () ; 
 int /*<<< orphan*/ * registry_machine_find (char*) ; 
 TYPE_2__* registry_person_find (char*) ; 
 int /*<<< orphan*/  registry_person_url_callback_verify_machine_exists ; 
 int /*<<< orphan*/  registry_set_person_cookie (struct web_client*,TYPE_2__*) ; 
 int /*<<< orphan*/  registry_unlock () ; 

int registry_request_switch_json(RRDHOST *host, struct web_client *w, char *person_guid, char *machine_guid, char *url, char *new_person_guid, time_t when) {
    if(!registry.enabled)
        return registry_json_disabled(host, w, "switch");

    (void)url;
    (void)when;

    registry_lock();

    REGISTRY_PERSON *op = registry_person_find(person_guid);
    if(!op) {
        registry_json_header(host, w, "switch", REGISTRY_STATUS_FAILED);
        registry_json_footer(w);
        registry_unlock();
        return 430;
    }

    REGISTRY_PERSON *np = registry_person_find(new_person_guid);
    if(!np) {
        registry_json_header(host, w, "switch", REGISTRY_STATUS_FAILED);
        registry_json_footer(w);
        registry_unlock();
        return 431;
    }

    REGISTRY_MACHINE *m = registry_machine_find(machine_guid);
    if(!m) {
        registry_json_header(host, w, "switch", REGISTRY_STATUS_FAILED);
        registry_json_footer(w);
        registry_unlock();
        return 432;
    }

    struct registry_person_url_callback_verify_machine_exists_data data = { m, 0 };

    // verify the old person has access to this machine
    avl_traverse(&op->person_urls, registry_person_url_callback_verify_machine_exists, &data);
    if(!data.count) {
        registry_json_header(host, w, "switch", REGISTRY_STATUS_FAILED);
        registry_json_footer(w);
        registry_unlock();
        return 433;
    }

    // verify the new person has access to this machine
    data.count = 0;
    avl_traverse(&np->person_urls, registry_person_url_callback_verify_machine_exists, &data);
    if(!data.count) {
        registry_json_header(host, w, "switch", REGISTRY_STATUS_FAILED);
        registry_json_footer(w);
        registry_unlock();
        return 434;
    }

    // set the cookie of the new person
    // the user just switched identity
    registry_set_person_cookie(w, np);

    // generate the response
    registry_json_header(host, w, "switch", REGISTRY_STATUS_OK);
    buffer_sprintf(w->response.data, ",\n\t\"person_guid\": \"%s\"", np->guid);
    registry_json_footer(w);

    registry_unlock();
    return 200;
}