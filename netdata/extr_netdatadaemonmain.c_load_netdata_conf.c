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
 int config_load (char*,char) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  netdata_configured_stock_config_dir ; 
 int /*<<< orphan*/  netdata_configured_user_config_dir ; 
 char* strdupz_path_subpath (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int load_netdata_conf(char *filename, char overwrite_used) {
    errno = 0;

    int ret = 0;

    if(filename && *filename) {
        ret = config_load(filename, overwrite_used);
        if(!ret)
            error("CONFIG: cannot load config file '%s'.", filename);
    }
    else {
        filename = strdupz_path_subpath(netdata_configured_user_config_dir, "netdata.conf");

        ret = config_load(filename, overwrite_used);
        if(!ret) {
            info("CONFIG: cannot load user config '%s'. Will try the stock version.", filename);
            freez(filename);

            filename = strdupz_path_subpath(netdata_configured_stock_config_dir, "netdata.conf");
            ret = config_load(filename, overwrite_used);
            if(!ret)
                info("CONFIG: cannot load stock config '%s'. Running with internal defaults.", filename);
        }

        freez(filename);
    }

    return ret;
}