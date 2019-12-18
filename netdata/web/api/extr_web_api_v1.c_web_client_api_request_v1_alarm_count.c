#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* data; } ;
struct web_client {TYPE_1__ response; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  contenttype; } ;
typedef  int /*<<< orphan*/  RRDHOST ;
typedef  int /*<<< orphan*/  RRDCALC_STATUS ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CT_APPLICATION_JSON ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int /*<<< orphan*/  RRDCALC_STATUS_CLEAR ; 
 int /*<<< orphan*/  RRDCALC_STATUS_CRITICAL ; 
 int /*<<< orphan*/  RRDCALC_STATUS_RAISED ; 
 int /*<<< orphan*/  RRDCALC_STATUS_REMOVED ; 
 int /*<<< orphan*/  RRDCALC_STATUS_UNDEFINED ; 
 int /*<<< orphan*/  RRDCALC_STATUS_UNINITIALIZED ; 
 int /*<<< orphan*/  RRDCALC_STATUS_WARNING ; 
 int /*<<< orphan*/ * buffer_create (int) ; 
 int /*<<< orphan*/  buffer_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_no_cacheable (TYPE_2__*) ; 
 int /*<<< orphan*/  buffer_sprintf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  health_aggregate_alarms (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* mystrsep (char**,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char toupper (char) ; 

inline int web_client_api_request_v1_alarm_count(RRDHOST *host, struct web_client *w, char *url) {
    RRDCALC_STATUS status = RRDCALC_STATUS_RAISED;
    BUFFER *contexts = NULL;

    buffer_flush(w->response.data);
    buffer_sprintf(w->response.data, "[");

    while(url) {
        char *value = mystrsep(&url, "&");
        if(!value || !*value) continue;

        char *name = mystrsep(&value, "=");
        if(!name || !*name) continue;
        if(!value || !*value) continue;

        debug(D_WEB_CLIENT, "%llu: API v1 alarm_count query param '%s' with value '%s'", w->id, name, value);

        char* p = value;
        if(!strcmp(name, "status")) {
            while ((*p = toupper(*p))) p++;
            if (!strcmp("CRITICAL", value)) status = RRDCALC_STATUS_CRITICAL;
            else if (!strcmp("WARNING", value)) status = RRDCALC_STATUS_WARNING;
            else if (!strcmp("UNINITIALIZED", value)) status = RRDCALC_STATUS_UNINITIALIZED;
            else if (!strcmp("UNDEFINED", value)) status = RRDCALC_STATUS_UNDEFINED;
            else if (!strcmp("REMOVED", value)) status = RRDCALC_STATUS_REMOVED;
            else if (!strcmp("CLEAR", value)) status = RRDCALC_STATUS_CLEAR;
        }
        else if(!strcmp(name, "context") || !strcmp(name, "ctx")) {
            if(!contexts) contexts = buffer_create(255);
            buffer_strcat(contexts, "|");
            buffer_strcat(contexts, value);
        }
    }

    health_aggregate_alarms(host, w->response.data, contexts, status);

    buffer_sprintf(w->response.data, "]\n");
    w->response.data->contenttype = CT_APPLICATION_JSON;
    buffer_no_cacheable(w->response.data);

    buffer_free(contexts);
    return 200;
}