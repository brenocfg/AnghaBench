#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rrdhost_system_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_BACKEND ; 
 int /*<<< orphan*/  CONFIG_SECTION_GLOBAL ; 
 int /*<<< orphan*/  D_RRDHOST ; 
 int /*<<< orphan*/  config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int config_get_number (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  default_health_enabled ; 
 int /*<<< orphan*/  default_rrd_history_entries ; 
 int /*<<< orphan*/  default_rrd_memory_mode ; 
 int /*<<< orphan*/  default_rrd_update_every ; 
 int /*<<< orphan*/  default_rrdpush_api_key ; 
 int /*<<< orphan*/  default_rrdpush_destination ; 
 int /*<<< orphan*/  default_rrdpush_enabled ; 
 int /*<<< orphan*/  default_rrdpush_send_charts_matching ; 
 int gap_when_lost_iterations_above ; 
 int /*<<< orphan*/  health_init () ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/  netdata_configured_timezone ; 
 int /*<<< orphan*/  os_type ; 
 int /*<<< orphan*/  program_name ; 
 int /*<<< orphan*/  program_version ; 
 int /*<<< orphan*/  registry_get_this_machine_guid () ; 
 int /*<<< orphan*/  registry_get_this_machine_hostname () ; 
 int /*<<< orphan*/  registry_init () ; 
 int /*<<< orphan*/  rrd_unlock () ; 
 int /*<<< orphan*/  rrd_wrlock () ; 
 int /*<<< orphan*/  rrdhost_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rrdhost_system_info*,int) ; 
 int /*<<< orphan*/  rrdpush_init () ; 
 int rrdset_free_obsolete_time ; 
 int /*<<< orphan*/  web_client_api_v1_management_init () ; 

void rrd_init(char *hostname, struct rrdhost_system_info *system_info) {
    rrdset_free_obsolete_time = config_get_number(CONFIG_SECTION_GLOBAL, "cleanup obsolete charts after seconds", rrdset_free_obsolete_time);
    gap_when_lost_iterations_above = (int)config_get_number(CONFIG_SECTION_GLOBAL, "gap when lost iterations above", gap_when_lost_iterations_above);
    if (gap_when_lost_iterations_above < 1)
        gap_when_lost_iterations_above = 1;

    health_init();
    registry_init();
    rrdpush_init();

    debug(D_RRDHOST, "Initializing localhost with hostname '%s'", hostname);
    rrd_wrlock();
    localhost = rrdhost_create(
            hostname
            , registry_get_this_machine_hostname()
            , registry_get_this_machine_guid()
            , os_type
            , netdata_configured_timezone
            , config_get(CONFIG_SECTION_BACKEND, "host tags", "")
            , program_name
            , program_version
            , default_rrd_update_every
            , default_rrd_history_entries
            , default_rrd_memory_mode
            , default_health_enabled
            , default_rrdpush_enabled
            , default_rrdpush_destination
            , default_rrdpush_api_key
            , default_rrdpush_send_charts_matching
            , system_info
            , 1
    );
    rrd_unlock();
	web_client_api_v1_management_init();
}