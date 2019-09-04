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
struct nfs_auth_info {int flavor_len; scalar_t__* flavors; } ;
typedef  scalar_t__ rpc_authflavor_t ;

/* Variables and functions */

bool nfs_auth_info_match(const struct nfs_auth_info *auth_info,
			 rpc_authflavor_t match)
{
	int i;

	if (!auth_info->flavor_len)
		return true;

	for (i = 0; i < auth_info->flavor_len; i++) {
		if (auth_info->flavors[i] == match)
			return true;
	}
	return false;
}