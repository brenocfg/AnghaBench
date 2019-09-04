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
 int /*<<< orphan*/  appconfig_load (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  netdata_configured_stock_config_dir ; 
 int /*<<< orphan*/  netdata_configured_user_config_dir ; 
 char* strdupz_path_subpath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stream_config ; 

__attribute__((used)) static void load_stream_conf() {
    errno = 0;
    char *filename = strdupz_path_subpath(netdata_configured_user_config_dir, "stream.conf");
    if(!appconfig_load(&stream_config, filename, 0)) {
        info("CONFIG: cannot load user config '%s'. Will try stock config.", filename);
        freez(filename);

        filename = strdupz_path_subpath(netdata_configured_stock_config_dir, "stream.conf");
        if(!appconfig_load(&stream_config, filename, 0))
            info("CONFIG: cannot load stock config '%s'. Running with internal defaults.", filename);
    }
    freez(filename);
}