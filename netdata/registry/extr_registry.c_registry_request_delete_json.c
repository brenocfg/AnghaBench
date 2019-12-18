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
struct web_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  RRDHOST ;
typedef  int /*<<< orphan*/  REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTRY_STATUS_FAILED ; 
 int /*<<< orphan*/  REGISTRY_STATUS_OK ; 
 TYPE_1__ registry ; 
 int registry_json_disabled (int /*<<< orphan*/ *,struct web_client*,char*) ; 
 int /*<<< orphan*/  registry_json_footer (struct web_client*) ; 
 int /*<<< orphan*/  registry_json_header (int /*<<< orphan*/ *,struct web_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_lock () ; 
 int /*<<< orphan*/ * registry_request_delete (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_unlock () ; 

int registry_request_delete_json(RRDHOST *host, struct web_client *w, char *person_guid, char *machine_guid, char *url, char *delete_url, time_t when) {
    if(!registry.enabled)
        return registry_json_disabled(host, w, "delete");

    registry_lock();

    REGISTRY_PERSON *p = registry_request_delete(person_guid, machine_guid, url, delete_url, when);
    if(!p) {
        registry_json_header(host, w, "delete", REGISTRY_STATUS_FAILED);
        registry_json_footer(w);
        registry_unlock();
        return 412;
    }

    // generate the response
    registry_json_header(host, w, "delete", REGISTRY_STATUS_OK);
    registry_json_footer(w);
    registry_unlock();
    return 200;
}