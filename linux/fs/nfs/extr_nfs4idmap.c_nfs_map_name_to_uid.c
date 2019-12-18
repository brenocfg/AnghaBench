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
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int __u32 ;
struct TYPE_2__ {struct idmap* cl_idmap; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  idmap_userns (struct idmap*) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int nfs_idmap_lookup_id (char const*,size_t,char*,int*,struct idmap*) ; 
 int /*<<< orphan*/  nfs_map_string_to_numeric (char const*,size_t,int*) ; 
 int /*<<< orphan*/  trace_nfs4_map_name_to_uid (char const*,size_t,int,int) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

int nfs_map_name_to_uid(const struct nfs_server *server, const char *name, size_t namelen, kuid_t *uid)
{
	struct idmap *idmap = server->nfs_client->cl_idmap;
	__u32 id = -1;
	int ret = 0;

	if (!nfs_map_string_to_numeric(name, namelen, &id))
		ret = nfs_idmap_lookup_id(name, namelen, "uid", &id, idmap);
	if (ret == 0) {
		*uid = make_kuid(idmap_userns(idmap), id);
		if (!uid_valid(*uid))
			ret = -ERANGE;
	}
	trace_nfs4_map_name_to_uid(name, namelen, id, ret);
	return ret;
}