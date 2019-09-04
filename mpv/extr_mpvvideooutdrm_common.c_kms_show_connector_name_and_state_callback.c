#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct TYPE_4__ {scalar_t__ connection; } ;
typedef  TYPE_1__ drmModeConnector ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTED ; 
 int MAX_CONNECTOR_NAME_LEN ; 
 int /*<<< orphan*/  get_connector_name (TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,char*,char const*) ; 

__attribute__((used)) static void kms_show_connector_name_and_state_callback(
    struct mp_log *log, int card_no, const drmModeConnector *connector)
{
    char other_connector_name[MAX_CONNECTOR_NAME_LEN];
    get_connector_name(connector, other_connector_name);
    const char *connection_str =
        (connector->connection == DRM_MODE_CONNECTED) ? "connected" : "disconnected";
    mp_info(log, "  %s (%s)\n", other_connector_name, connection_str);
}