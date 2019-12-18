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
struct nfs_auth_info {scalar_t__* flavors; unsigned int flavor_len; } ;
typedef  scalar_t__ rpc_authflavor_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  MOUNT ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool nfs_auth_info_add(struct nfs_auth_info *auth_info,
			      rpc_authflavor_t flavor)
{
	unsigned int i;
	unsigned int max_flavor_len = ARRAY_SIZE(auth_info->flavors);

	/* make sure this flavor isn't already in the list */
	for (i = 0; i < auth_info->flavor_len; i++) {
		if (flavor == auth_info->flavors[i])
			return true;
	}

	if (auth_info->flavor_len + 1 >= max_flavor_len) {
		dfprintk(MOUNT, "NFS: too many sec= flavors\n");
		return false;
	}

	auth_info->flavors[auth_info->flavor_len++] = flavor;
	return true;
}