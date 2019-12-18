#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {TYPE_1__* nfs_client; } ;
struct idmap {int dummy; } ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int __u32 ;
struct TYPE_2__ {struct idmap* cl_idmap; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmap_userns (struct idmap*) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int nfs_idmap_lookup_id (char const*,size_t,char*,int*,struct idmap*) ; 
 int /*<<< orphan*/  nfs_map_string_to_numeric (char const*,size_t,int*) ; 
 int /*<<< orphan*/  trace_nfs4_map_group_to_gid (char const*,size_t,int,int) ; 

int nfs_map_group_to_gid(const struct nfs_server *server, const char *name, size_t namelen, kgid_t *gid)
{
	struct idmap *idmap = server->nfs_client->cl_idmap;
	__u32 id = -1;
	int ret = 0;

	if (!nfs_map_string_to_numeric(name, namelen, &id))
		ret = nfs_idmap_lookup_id(name, namelen, "gid", &id, idmap);
	if (ret == 0) {
		*gid = make_kgid(idmap_userns(idmap), id);
		if (!gid_valid(*gid))
			ret = -ERANGE;
	}
	trace_nfs4_map_group_to_gid(name, namelen, id, ret);
	return ret;
}