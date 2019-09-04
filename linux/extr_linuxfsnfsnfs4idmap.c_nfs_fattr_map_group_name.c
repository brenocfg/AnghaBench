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
struct nfs_server {int dummy; } ;
struct nfs_fattr {int valid; int /*<<< orphan*/  gid; struct nfs4_string* group_name; } ;
struct nfs4_string {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int NFS_ATTR_FATTR_GROUP ; 
 int NFS_ATTR_FATTR_GROUP_NAME ; 
 scalar_t__ nfs_map_group_to_gid (struct nfs_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs_fattr_map_group_name(struct nfs_server *server, struct nfs_fattr *fattr)
{
	struct nfs4_string *group = fattr->group_name;
	kgid_t gid;

	if (!(fattr->valid & NFS_ATTR_FATTR_GROUP_NAME))
		return false;
	if (nfs_map_group_to_gid(server, group->data, group->len, &gid) == 0) {
		fattr->gid = gid;
		fattr->valid |= NFS_ATTR_FATTR_GROUP;
	}
	return true;
}