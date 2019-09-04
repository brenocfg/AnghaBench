#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* data; } ;
struct web_client {TYPE_1__ response; } ;
struct TYPE_15__ {int /*<<< orphan*/  contenttype; } ;
struct TYPE_14__ {int /*<<< orphan*/  machine_guid; int /*<<< orphan*/  program_version; } ;
typedef  TYPE_2__ RRDHOST ;
typedef  TYPE_3__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CT_APPLICATION_JSON ; 
 int /*<<< orphan*/  buffer_flush (TYPE_3__*) ; 
 int /*<<< orphan*/  buffer_sprintf (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_strcat (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  chartcollectors2json (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  netdata_ready ; 
 int /*<<< orphan*/  web_client_api_request_v1_info_mirrored_hosts (TYPE_3__*) ; 
 int /*<<< orphan*/  web_client_api_request_v1_info_summary_alarm_statuses (TYPE_2__*,TYPE_3__*) ; 

inline int web_client_api_request_v1_info(RRDHOST *host, struct web_client *w, char *url) {
    (void)url;
    if (!netdata_ready) return 400;

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

    buffer_sprintf(wb, "\t\"os_name\": %s,\n", getenv("NETDATA_SYSTEM_OS_NAME"));
    buffer_sprintf(wb, "\t\"os_id\": \"%s\",\n", getenv("NETDATA_SYSTEM_OS_ID"));
    buffer_sprintf(wb, "\t\"os_id_like\": \"%s\",\n", getenv("NETDATA_SYSTEM_OS_ID_LIKE"));
    buffer_sprintf(wb, "\t\"os_version\": \"%s\",\n", getenv("NETDATA_SYSTEM_OS_VERSION"));
    buffer_sprintf(wb, "\t\"os_version_id\": \"%s\",\n", getenv("NETDATA_SYSTEM_OS_VERSION_ID"));
    buffer_sprintf(wb, "\t\"os_detection\": \"%s\",\n", getenv("NETDATA_SYSTEM_OS_DETECTION"));
    buffer_sprintf(wb, "\t\"kernel_name\": \"%s\",\n", getenv("NETDATA_SYSTEM_KERNEL_NAME"));
    buffer_sprintf(wb, "\t\"kernel_version\": \"%s\",\n", getenv("NETDATA_SYSTEM_KERNEL_VERSION"));
    buffer_sprintf(wb, "\t\"architecture\": \"%s\",\n", getenv("NETDATA_SYSTEM_ARCHITECTURE"));
    buffer_sprintf(wb, "\t\"virtualization\": \"%s\",\n", getenv("NETDATA_SYSTEM_VIRTUALIZATION"));
    buffer_sprintf(wb, "\t\"virt_detection\": \"%s\",\n", getenv("NETDATA_SYSTEM_VIRT_DETECTION"));
    buffer_sprintf(wb, "\t\"container\": \"%s\",\n", getenv("NETDATA_SYSTEM_CONTAINER"));
    buffer_sprintf(wb, "\t\"container_detection\": \"%s\",\n", getenv("NETDATA_SYSTEM_CONTAINER_DETECTION"));
    
    buffer_strcat(wb, "\t\"collectors\": [");
    chartcollectors2json(host, wb);
    buffer_strcat(wb, "\n\t]\n");

    buffer_strcat(wb, "}");
    return 200;
}