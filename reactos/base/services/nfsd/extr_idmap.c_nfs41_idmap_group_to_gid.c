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
struct idmap_lookup {char const* value; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct idmap_group {int gid; } ;
struct idmap_context {int dummy; } ;
typedef  int gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_GROUP_NAME ; 
 int /*<<< orphan*/  CLASS_GROUP ; 
 int /*<<< orphan*/  IDLVL ; 
 int /*<<< orphan*/  TYPE_STR ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  group_cmp ; 
 int idmap_lookup_group (struct idmap_context*,struct idmap_lookup*,struct idmap_group*) ; 

int nfs41_idmap_group_to_gid(
    struct idmap_context *context,
    const char *name,
    gid_t *gid_out)
{
    struct idmap_lookup lookup = { ATTR_GROUP_NAME,
        CLASS_GROUP, TYPE_STR, group_cmp };
    struct idmap_group group;
    int status;

    dprintf(IDLVL, "--> nfs41_idmap_group_to_gid('%s')\n", name);

    lookup.value = name;

    /* look up the group entry */
    status = idmap_lookup_group(context, &lookup, &group);
    if (status) {
        dprintf(IDLVL, "<-- nfs41_idmap_group_to_gid('%s') "
            "failed with %d\n", name, status);
        goto out;
    }

    *gid_out = group.gid;
    dprintf(IDLVL, "<-- nfs41_idmap_group_to_gid('%s') "
        "returning %u\n", name, group.gid);
out:
    return status;
}