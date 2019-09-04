#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {TYPE_2__* data; } ;
struct web_client {TYPE_1__ response; } ;
struct TYPE_5__ {int /*<<< orphan*/  contenttype; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  CT_APPLICATION_JSON ; 
 int /*<<< orphan*/  buffer_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  health_alarm_log2json (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 char* mystrsep (char**,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

inline int web_client_api_request_v1_alarm_log(RRDHOST *host, struct web_client *w, char *url) {
    uint32_t after = 0;

    while(url) {
        char *value = mystrsep(&url, "&");
        if (!value || !*value) continue;

        char *name = mystrsep(&value, "=");
        if(!name || !*name) continue;
        if(!value || !*value) continue;

        if(!strcmp(name, "after")) after = (uint32_t)strtoul(value, NULL, 0);
    }

    buffer_flush(w->response.data);
    w->response.data->contenttype = CT_APPLICATION_JSON;
    health_alarm_log2json(host, w->response.data, after);
    return 200;
}