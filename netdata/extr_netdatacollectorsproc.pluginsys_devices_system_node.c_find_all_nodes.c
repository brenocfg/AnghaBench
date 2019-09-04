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
struct stat {int dummy; } ;
struct node {struct node* next; void* numastat_filename; struct node* name; } ;
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 struct node* callocz (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* config_get (char*,char*,char*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  freez (struct node*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 char* netdata_configured_host_prefix ; 
 struct node* numa_root ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 void* strdupz (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int find_all_nodes() {
    int numa_node_count = 0;
    char name[FILENAME_MAX + 1];
    snprintfz(name, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/node");
    char *dirname = config_get("plugin:proc:/sys/devices/system/node", "directory to monitor", name);

    DIR *dir = opendir(dirname);
    if(!dir) {
        error("Cannot read NUMA node directory '%s'", dirname);
        return 0;
    }

    struct dirent *de = NULL;
    while((de = readdir(dir))) {
        if(de->d_type != DT_DIR)
            continue;

        if(strncmp(de->d_name, "node", 4) != 0)
            continue;

        if(!isdigit(de->d_name[4]))
            continue;

        numa_node_count++;

        struct node *m = callocz(1, sizeof(struct node));
        m->name = strdupz(de->d_name);

        struct stat st;

        snprintfz(name, FILENAME_MAX, "%s/%s/numastat", dirname, de->d_name);
        if(stat(name, &st) == -1) {
            freez(m->name);
            freez(m);
            continue;
        }

        m->numastat_filename = strdupz(name);

        m->next = numa_root;
        numa_root = m;
    }

    closedir(dir);

    return numa_node_count;
}