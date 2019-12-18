#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct web_client {TYPE_1__ response; } ;
struct TYPE_4__ {int /*<<< orphan*/  cloud_base_url; int /*<<< orphan*/  registry_to_announce; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTRY_STATUS_OK ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ netdata_anonymous_statistics_enabled ; 
 TYPE_2__ registry ; 
 int /*<<< orphan*/  registry_json_footer (struct web_client*) ; 
 int /*<<< orphan*/  registry_json_header (int /*<<< orphan*/ *,struct web_client*,char*,int /*<<< orphan*/ ) ; 

int registry_request_hello_json(RRDHOST *host, struct web_client *w) {
    registry_json_header(host, w, "hello", REGISTRY_STATUS_OK);

    buffer_sprintf(w->response.data,
            ",\n\t\"registry\": \"%s\",\n\t\"cloud_base_url\": \"%s\",\n\t\"anonymous_statistics\": %s",
            registry.registry_to_announce,
            registry.cloud_base_url, netdata_anonymous_statistics_enabled?"true":"false");

    registry_json_footer(w);
    return 200;
}