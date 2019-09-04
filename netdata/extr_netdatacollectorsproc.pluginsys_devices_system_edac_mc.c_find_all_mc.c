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
struct mc {struct mc* next; struct mc* name; void* ue_count_filename; void* ce_count_filename; } ;
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 struct mc* callocz (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* config_get (char*,char*,char*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  freez (struct mc*) ; 
 scalar_t__ isdigit (char) ; 
 struct mc* mc_root ; 
 char* netdata_configured_host_prefix ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 void* strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void find_all_mc() {
    char name[FILENAME_MAX + 1];
    snprintfz(name, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/edac/mc");
    char *dirname = config_get("plugin:proc:/sys/devices/system/edac/mc", "directory to monitor", name);

    DIR *dir = opendir(dirname);
    if(unlikely(!dir)) {
        error("Cannot read ECC memory errors directory '%s'", dirname);
        return;
    }

    struct dirent *de = NULL;
    while((de = readdir(dir))) {
        if(de->d_type == DT_DIR && de->d_name[0] == 'm' && de->d_name[1] == 'c' && isdigit(de->d_name[2])) {
            struct mc *m = callocz(1, sizeof(struct mc));
            m->name = strdupz(de->d_name);

            struct stat st;

            snprintfz(name, FILENAME_MAX, "%s/%s/ce_count", dirname, de->d_name);
            if(stat(name, &st) != -1)
                m->ce_count_filename = strdupz(name);

            snprintfz(name, FILENAME_MAX, "%s/%s/ue_count", dirname, de->d_name);
            if(stat(name, &st) != -1)
                m->ue_count_filename = strdupz(name);

            if(!m->ce_count_filename && !m->ue_count_filename) {
                freez(m->name);
                freez(m);
            }
            else {
                m->next = mc_root;
                mc_root = m;
            }
        }
    }

    closedir(dir);
}