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
struct TYPE_4__ {int /*<<< orphan*/  registry_to_announce; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTRY_STATUS_DISABLED ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ registry ; 
 int /*<<< orphan*/  registry_json_footer (struct web_client*) ; 
 int /*<<< orphan*/  registry_json_header (int /*<<< orphan*/ *,struct web_client*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int registry_json_disabled(RRDHOST *host, struct web_client *w, const char *action) {
    registry_json_header(host, w, action, REGISTRY_STATUS_DISABLED);

    buffer_sprintf(w->response.data, ",\n\t\"registry\": \"%s\"",
            registry.registry_to_announce);

    registry_json_footer(w);
    return 200;
}