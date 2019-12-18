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
 int /*<<< orphan*/  netdata_fix_chart_id (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,size_t,char*,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static inline char *cgroup_chart_type(char *buffer, const char *id, size_t len) {
    if(buffer[0]) return buffer;

    if(id[0] == '\0' || (id[0] == '/' && id[1] == '\0'))
        strncpy(buffer, "cgroup_root", len);
    else
        snprintfz(buffer, len, "cgroup_%s", id);

    netdata_fix_chart_id(buffer);
    return buffer;
}