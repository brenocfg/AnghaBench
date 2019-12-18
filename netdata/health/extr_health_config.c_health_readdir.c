#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hostname; int /*<<< orphan*/  health_enabled; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_HEALTH ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  health_readfile ; 
 int /*<<< orphan*/  recursive_config_double_dir_load (char const*,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void health_readdir(RRDHOST *host, const char *user_path, const char *stock_path, const char *subpath) {
    if(unlikely(!host->health_enabled)) {
        debug(D_HEALTH, "CONFIG health is not enabled for host '%s'", host->hostname);
        return;
    }

    recursive_config_double_dir_load(user_path, stock_path, subpath, health_readfile, (void *) host, 0);
}