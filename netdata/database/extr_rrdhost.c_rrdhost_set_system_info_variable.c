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
struct rrdhost_system_info {void* container_detection; void* container; void* virt_detection; void* virtualization; void* architecture; void* kernel_version; void* kernel_name; void* os_detection; void* os_version_id; void* os_version; void* os_id_like; void* os_id; void* os_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdupz (char*) ; 

int rrdhost_set_system_info_variable(struct rrdhost_system_info *system_info, char *name, char *value) {
    int res = 0;

    if(!strcmp(name, "NETDATA_SYSTEM_OS_NAME")){
        freez(system_info->os_name);
        system_info->os_name = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_OS_ID")){
        freez(system_info->os_id);
        system_info->os_id = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_OS_ID_LIKE")){
        freez(system_info->os_id_like);
        system_info->os_id_like = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_OS_VERSION")){
        freez(system_info->os_version);
        system_info->os_version = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_OS_VERSION_ID")){
        freez(system_info->os_version_id);
        system_info->os_version_id = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_OS_DETECTION")){
        freez(system_info->os_detection);
        system_info->os_detection = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_KERNEL_NAME")){
        freez(system_info->kernel_name);
        system_info->kernel_name = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_KERNEL_VERSION")){
        freez(system_info->kernel_version);
        system_info->kernel_version = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_ARCHITECTURE")){
        freez(system_info->architecture);
        system_info->architecture = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_VIRTUALIZATION")){
        freez(system_info->virtualization);
        system_info->virtualization = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_VIRT_DETECTION")){
        freez(system_info->virt_detection);
        system_info->virt_detection = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_CONTAINER")){
        freez(system_info->container);
        system_info->container = strdupz(value);
    }
    else if(!strcmp(name, "NETDATA_SYSTEM_CONTAINER_DETECTION")){
        freez(system_info->container_detection);
        system_info->container_detection = strdupz(value);
    }
    else {
        res = 1;
    }

    return res;
}