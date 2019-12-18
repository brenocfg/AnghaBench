#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* data; } ;
struct web_client {TYPE_1__ response; } ;
struct TYPE_18__ {int /*<<< orphan*/  contenttype; } ;
struct TYPE_17__ {char* program_version; char* machine_guid; TYPE_2__* system_info; } ;
struct TYPE_16__ {char* os_name; char* os_id; char* os_id_like; char* os_version; char* os_version_id; char* os_detection; char* kernel_name; char* kernel_version; char* architecture; char* virtualization; char* virt_detection; char* container; char* container_detection; } ;
typedef  TYPE_3__ RRDHOST ;
typedef  TYPE_4__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CT_APPLICATION_JSON ; 
 int HTTP_RESP_BACKEND_FETCH_FAILED ; 
 int HTTP_RESP_OK ; 
 int /*<<< orphan*/  buffer_flush (TYPE_4__*) ; 
 int /*<<< orphan*/  buffer_no_cacheable (TYPE_4__*) ; 
 int /*<<< orphan*/  buffer_sprintf (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  chartcollectors2json (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  netdata_ready ; 
 int /*<<< orphan*/  web_client_api_request_v1_info_mirrored_hosts (TYPE_4__*) ; 
 int /*<<< orphan*/  web_client_api_request_v1_info_summary_alarm_statuses (TYPE_3__*,TYPE_4__*) ; 

inline int web_client_api_request_v1_info(RRDHOST *host, struct web_client *w, char *url) {
    (void)url;
    if (!netdata_ready) return HTTP_RESP_BACKEND_FETCH_FAILED;

    BUFFER *wb = w->response.data;
    buffer_flush(wb);
    wb->contenttype = CT_APPLICATION_JSON;

    buffer_strcat(wb, "{\n");
    buffer_sprintf(wb, "\t\"version\": \"%s\",\n", host->program_version);
    buffer_sprintf(wb, "\t\"uid\": \"%s\",\n", host->machine_guid);

    buffer_strcat(wb, "\t\"mirrored_hosts\": [\n");
    web_client_api_request_v1_info_mirrored_hosts(wb);
    buffer_strcat(wb, "\t],\n");

    buffer_strcat(wb, "\t\"alarms\": {\n");
    web_client_api_request_v1_info_summary_alarm_statuses(host, wb);
    buffer_strcat(wb, "\t},\n");

    buffer_sprintf(wb, "\t\"os_name\": %s,\n", (host->system_info->os_name) ? host->system_info->os_name : "\"\"");
    buffer_sprintf(wb, "\t\"os_id\": \"%s\",\n", (host->system_info->os_id) ? host->system_info->os_id : "");
    buffer_sprintf(wb, "\t\"os_id_like\": \"%s\",\n", (host->system_info->os_id_like) ? host->system_info->os_id_like : "");
    buffer_sprintf(wb, "\t\"os_version\": \"%s\",\n", (host->system_info->os_version) ? host->system_info->os_version : "");
    buffer_sprintf(wb, "\t\"os_version_id\": \"%s\",\n", (host->system_info->os_version_id) ? host->system_info->os_version_id : "");
    buffer_sprintf(wb, "\t\"os_detection\": \"%s\",\n", (host->system_info->os_detection) ? host->system_info->os_detection : "");
    buffer_sprintf(wb, "\t\"kernel_name\": \"%s\",\n", (host->system_info->kernel_name) ? host->system_info->kernel_name : "");
    buffer_sprintf(wb, "\t\"kernel_version\": \"%s\",\n", (host->system_info->kernel_version) ? host->system_info->kernel_version : "");
    buffer_sprintf(wb, "\t\"architecture\": \"%s\",\n", (host->system_info->architecture) ? host->system_info->architecture : "");
    buffer_sprintf(wb, "\t\"virtualization\": \"%s\",\n", (host->system_info->virtualization) ? host->system_info->virtualization : "");
    buffer_sprintf(wb, "\t\"virt_detection\": \"%s\",\n", (host->system_info->virt_detection) ? host->system_info->virt_detection : "");
    buffer_sprintf(wb, "\t\"container\": \"%s\",\n", (host->system_info->container) ? host->system_info->container : "");
    buffer_sprintf(wb, "\t\"container_detection\": \"%s\",\n", (host->system_info->container_detection) ? host->system_info->container_detection : "");

    buffer_strcat(wb, "\t\"collectors\": [");
    chartcollectors2json(host, wb);
    buffer_strcat(wb, "\n\t]\n");

    buffer_strcat(wb, "}");
    buffer_no_cacheable(wb);
    return HTTP_RESP_OK;
}