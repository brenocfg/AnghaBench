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
struct nfs_fattr {int valid; int /*<<< orphan*/  uid; struct nfs4_string* owner_name; } ;
struct nfs4_string {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int NFS_ATTR_FATTR_OWNER ; 
 int NFS_ATTR_FATTR_OWNER_NAME ; 
 scalar_t__ nfs_map_name_to_uid (struct nfs_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs_fattr_map_owner_name(struct nfs_server *server, struct nfs_fattr *fattr)
{
	struct nfs4_string *owner = fattr->owner_name;
	kuid_t uid;

	if (!(fattr->valid & NFS_ATTR_FATTR_OWNER_NAME))
		return false;
	if (nfs_map_name_to_uid(server, owner->data, owner->len, &uid) == 0) {
		fattr->uid = uid;
		fattr->valid |= NFS_ATTR_FATTR_OWNER;
	}
	return true;
}