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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_PLUGINS ; 
 char* config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  default_rrd_update_every ; 
 int /*<<< orphan*/  get_system_timezone () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  netdata_configured_cache_dir ; 
 int /*<<< orphan*/  netdata_configured_home_dir ; 
 char* netdata_configured_host_prefix ; 
 char* netdata_configured_hostname ; 
 int /*<<< orphan*/  netdata_configured_log_dir ; 
 int /*<<< orphan*/  netdata_configured_primary_plugins_dir ; 
 int /*<<< orphan*/  netdata_configured_stock_config_dir ; 
 int /*<<< orphan*/  netdata_configured_user_config_dir ; 
 int /*<<< orphan*/  netdata_configured_varlib_dir ; 
 int /*<<< orphan*/  netdata_configured_web_dir ; 
 char* program_version ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char*,...) ; 
 char* verify_required_directory (int /*<<< orphan*/ ) ; 

void set_global_environment() {
    {
        char b[16];
        snprintfz(b, 15, "%d", default_rrd_update_every);
        setenv("NETDATA_UPDATE_EVERY", b, 1);
    }

    setenv("NETDATA_VERSION"          , program_version, 1);
    setenv("NETDATA_HOSTNAME"         , netdata_configured_hostname, 1);
    setenv("NETDATA_CONFIG_DIR"       , verify_required_directory(netdata_configured_user_config_dir),  1);
    setenv("NETDATA_USER_CONFIG_DIR"  , verify_required_directory(netdata_configured_user_config_dir),  1);
    setenv("NETDATA_STOCK_CONFIG_DIR" , verify_required_directory(netdata_configured_stock_config_dir), 1);
    setenv("NETDATA_PLUGINS_DIR"      , verify_required_directory(netdata_configured_primary_plugins_dir),      1);
    setenv("NETDATA_WEB_DIR"          , verify_required_directory(netdata_configured_web_dir),          1);
    setenv("NETDATA_CACHE_DIR"        , verify_required_directory(netdata_configured_cache_dir),        1);
    setenv("NETDATA_LIB_DIR"          , verify_required_directory(netdata_configured_varlib_dir),       1);
    setenv("NETDATA_LOG_DIR"          , verify_required_directory(netdata_configured_log_dir),          1);
    setenv("HOME"                     , verify_required_directory(netdata_configured_home_dir),         1);
    setenv("NETDATA_HOST_PREFIX"      , netdata_configured_host_prefix, 1);

    get_system_timezone();

    // set the path we need
    char path[1024 + 1], *p = getenv("PATH");
    if(!p) p = "/bin:/usr/bin";
    snprintfz(path, 1024, "%s:%s", p, "/sbin:/usr/sbin:/usr/local/bin:/usr/local/sbin");
    setenv("PATH", config_get(CONFIG_SECTION_PLUGINS, "PATH environment variable", path), 1);

    // python options
    p = getenv("PYTHONPATH");
    if(!p) p = "";
    setenv("PYTHONPATH", config_get(CONFIG_SECTION_PLUGINS, "PYTHONPATH environment variable", p), 1);

    // disable buffering for python plugins
    setenv("PYTHONUNBUFFERED", "1", 1);

    // switch to standard locale for plugins
    setenv("LC_ALL", "C", 1);
}