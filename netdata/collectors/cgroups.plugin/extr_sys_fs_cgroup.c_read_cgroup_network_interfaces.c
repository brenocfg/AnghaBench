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
struct cgroup_network_interface {void* container_device; void* host_device; struct cgroup_network_interface* next; } ;
struct cgroup {int options; int /*<<< orphan*/  chart_id; int /*<<< orphan*/  id; struct cgroup_network_interface* interfaces; int /*<<< orphan*/  chart_title; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_NETWORK_INTERFACE_MAX_LINE ; 
 int CGROUP_OPTIONS_IS_UNIFIED ; 
 int /*<<< orphan*/  D_CGROUP ; 
 struct cgroup_network_interface* callocz (int,int) ; 
 int /*<<< orphan*/  cgroup_cpuacct_base ; 
 int /*<<< orphan*/  cgroup_unified_base ; 
 int /*<<< orphan*/  cgroups_network_interface_script ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 char* fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  mypclose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mypopen (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_rename_device_add (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strdupz (char*) ; 
 int /*<<< orphan*/  trim (char*) ; 

__attribute__((used)) static inline void read_cgroup_network_interfaces(struct cgroup *cg) {
    debug(D_CGROUP, "looking for the network interfaces of cgroup '%s' with chart id '%s' and title '%s'", cg->id, cg->chart_id, cg->chart_title);

    pid_t cgroup_pid;
    char command[CGROUP_NETWORK_INTERFACE_MAX_LINE + 1];

    if(!(cg->options & CGROUP_OPTIONS_IS_UNIFIED)) {
        snprintfz(command, CGROUP_NETWORK_INTERFACE_MAX_LINE, "exec %s --cgroup '%s%s'", cgroups_network_interface_script, cgroup_cpuacct_base, cg->id);
    }
    else {
        snprintfz(command, CGROUP_NETWORK_INTERFACE_MAX_LINE, "exec %s --cgroup '%s%s'", cgroups_network_interface_script, cgroup_unified_base, cg->id);
    }

    debug(D_CGROUP, "executing command '%s' for cgroup '%s'", command, cg->id);
    FILE *fp = mypopen(command, &cgroup_pid);
    if(!fp) {
        error("CGROUP: cannot popen(\"%s\", \"r\").", command);
        return;
    }

    char *s;
    char buffer[CGROUP_NETWORK_INTERFACE_MAX_LINE + 1];
    while((s = fgets(buffer, CGROUP_NETWORK_INTERFACE_MAX_LINE, fp))) {
        trim(s);

        if(*s && *s != '\n') {
            char *t = s;
            while(*t && *t != ' ') t++;
            if(*t == ' ') {
                *t = '\0';
                t++;
            }

            if(!*s) {
                error("CGROUP: empty host interface returned by script");
                continue;
            }

            if(!*t) {
                error("CGROUP: empty guest interface returned by script");
                continue;
            }

            struct cgroup_network_interface *i = callocz(1, sizeof(struct cgroup_network_interface));
            i->host_device = strdupz(s);
            i->container_device = strdupz(t);
            i->next = cg->interfaces;
            cg->interfaces = i;

            info("CGROUP: cgroup '%s' has network interface '%s' as '%s'", cg->id, i->host_device, i->container_device);

            // register a device rename to proc_net_dev.c
            netdev_rename_device_add(i->host_device, i->container_device, cg->chart_id);
        }
    }

    mypclose(fp, cgroup_pid);
    // debug(D_CGROUP, "closed command for cgroup '%s'", cg->id);
}