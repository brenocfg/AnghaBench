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
struct dirent {scalar_t__ d_type; int /*<<< orphan*/ * d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* config_get (char*,char*,char*) ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

int get_numa_node_count(void)
{
    static int numa_node_count = -1;

    if (numa_node_count != -1)
        return numa_node_count;

    numa_node_count = 0;

    char name[FILENAME_MAX + 1];
    snprintfz(name, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/node");
    char *dirname = config_get("plugin:proc:/sys/devices/system/node", "directory to monitor", name);

    DIR *dir = opendir(dirname);
    if(dir) {
        struct dirent *de = NULL;
        while((de = readdir(dir))) {
            if(de->d_type != DT_DIR)
                continue;

            if(strncmp(de->d_name, "node", 4) != 0)
                continue;

            if(!isdigit(de->d_name[4]))
                continue;

            numa_node_count++;
        }
        closedir(dir);
    }

    return numa_node_count;
}