#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_9__ {TYPE_6__* data; } ;
struct web_client {TYPE_1__ response; } ;
struct registry_json_walk_person_urls_callback {int /*<<< orphan*/  member_3; struct web_client* member_2; int /*<<< orphan*/ * member_1; TYPE_2__* member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  contenttype; } ;
struct TYPE_11__ {scalar_t__ verify_cookies_redirects; int /*<<< orphan*/  registry_to_announce; int /*<<< orphan*/  enabled; } ;
struct TYPE_10__ {int /*<<< orphan*/  person_urls; int /*<<< orphan*/  guid; } ;
typedef  int /*<<< orphan*/  RRDHOST ;
typedef  TYPE_2__ REGISTRY_PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  CT_APPLICATION_JSON ; 
 int /*<<< orphan*/  REGISTRY_STATUS_FAILED ; 
 int /*<<< orphan*/  REGISTRY_STATUS_OK ; 
 int /*<<< orphan*/  REGISTRY_VERIFY_COOKIES_GUID ; 
 int /*<<< orphan*/  avl_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct registry_json_walk_person_urls_callback*) ; 
 int /*<<< orphan*/  buffer_flush (TYPE_6__*) ; 
 int /*<<< orphan*/  buffer_sprintf (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_6__*,char*) ; 
 TYPE_5__ registry ; 
 int registry_json_disabled (int /*<<< orphan*/ *,struct web_client*,char*) ; 
 int /*<<< orphan*/  registry_json_footer (struct web_client*) ; 
 int /*<<< orphan*/  registry_json_header (int /*<<< orphan*/ *,struct web_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_json_person_url_callback ; 
 int /*<<< orphan*/  registry_lock () ; 
 TYPE_2__* registry_request_access (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_set_cookie (struct web_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_set_person_cookie (struct web_client*,TYPE_2__*) ; 
 int /*<<< orphan*/  registry_unlock () ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int registry_request_access_json(RRDHOST *host, struct web_client *w, char *person_guid, char *machine_guid, char *url, char *name, time_t when) {
    if(unlikely(!registry.enabled))
        return registry_json_disabled(host, w, "access");

    // ------------------------------------------------------------------------
    // verify the browser supports cookies

    if(registry.verify_cookies_redirects > 0 && !person_guid[0]) {
        buffer_flush(w->response.data);
        registry_set_cookie(w, REGISTRY_VERIFY_COOKIES_GUID);
        w->response.data->contenttype = CT_APPLICATION_JSON;
        buffer_sprintf(w->response.data, "{ \"status\": \"redirect\", \"registry\": \"%s\" }", registry.registry_to_announce);
        return 200;
    }

    if(unlikely(person_guid[0] && !strcmp(person_guid, REGISTRY_VERIFY_COOKIES_GUID)))
        person_guid[0] = '\0';

    // ------------------------------------------------------------------------

    registry_lock();

    REGISTRY_PERSON *p = registry_request_access(person_guid, machine_guid, url, name, when);
    if(!p) {
        registry_json_header(host, w, "access", REGISTRY_STATUS_FAILED);
        registry_json_footer(w);
        registry_unlock();
        return 412;
    }

    // set the cookie
    registry_set_person_cookie(w, p);

    // generate the response
    registry_json_header(host, w, "access", REGISTRY_STATUS_OK);

    buffer_sprintf(w->response.data, ",\n\t\"person_guid\": \"%s\",\n\t\"urls\": [", p->guid);
    struct registry_json_walk_person_urls_callback c = { p, NULL, w, 0 };
    avl_traverse(&p->person_urls, registry_json_person_url_callback, &c);
    buffer_strcat(w->response.data, "\n\t]\n");

    registry_json_footer(w);
    registry_unlock();
    return 200;
}