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
typedef  int /*<<< orphan*/  uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,char const*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int uuid_parse (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_unparse_lower (int /*<<< orphan*/ ,char*) ; 

int regenerate_guid(const char *guid, char *result) {
    uuid_t uuid;
    if(unlikely(uuid_parse(guid, uuid) == -1)) {
        info("Registry: GUID '%s' is not a valid GUID.", guid);
        return -1;
    }
    else {
        uuid_unparse_lower(uuid, result);

#ifdef NETDATA_INTERNAL_CHECKS
        if(strcmp(guid, result) != 0)
            info("GUID '%s' and re-generated GUID '%s' differ!", guid, result);
#endif /* NETDATA_INTERNAL_CHECKS */
    }

    return 0;
}