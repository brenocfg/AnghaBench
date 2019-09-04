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
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static inline int is_machine_guid_blacklisted(const char *guid) {
    // these are machine GUIDs that have been included in distribution packages.
    // we blacklist them here, so that the next version of netdata will generate
    // new ones.

    if(!strcmp(guid, "8a795b0c-2311-11e6-8563-000c295076a6")
       || !strcmp(guid, "4aed1458-1c3e-11e6-a53f-000c290fc8f5")
            ) {
        error("Blacklisted machine GUID '%s' found.", guid);
        return 1;
    }

    return 0;
}