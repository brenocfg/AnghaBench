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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  REGISTRY_MACHINE ;

/* Variables and functions */
 int /*<<< orphan*/  GUID_LEN ; 
 int /*<<< orphan*/  info (char*,char const*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int regenerate_guid (char const*,char*) ; 
 int /*<<< orphan*/ * registry_machine_allocate (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * registry_machine_find (char const*) ; 
 scalar_t__ unlikely (int) ; 

REGISTRY_MACHINE *registry_machine_get(const char *machine_guid, time_t when) {
    REGISTRY_MACHINE *m = NULL;

    if(likely(machine_guid && *machine_guid)) {
        // validate it is a GUID
        char buf[GUID_LEN + 1];
        if(unlikely(regenerate_guid(machine_guid, buf) == -1))
            info("Registry: machine guid '%s' is not a valid guid. Ignoring it.", machine_guid);
        else {
            machine_guid = buf;
            m = registry_machine_find(machine_guid);
            if(!m) m = registry_machine_allocate(machine_guid, when);
        }
    }

    return m;
}