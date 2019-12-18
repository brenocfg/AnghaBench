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
struct TYPE_2__ {scalar_t__* flavors; } ;
struct nfs_parsed_mount_data {scalar_t__ selected_flavor; TYPE_1__ auth_info; } ;
typedef  scalar_t__ rpc_authflavor_t ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  MOUNT ; 
 scalar_t__ RPC_AUTH_MAXFLAVOR ; 
 scalar_t__ RPC_AUTH_NULL ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ nfs_auth_info_match (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int nfs_verify_authflavors(struct nfs_parsed_mount_data *args,
			rpc_authflavor_t *server_authlist, unsigned int count)
{
	rpc_authflavor_t flavor = RPC_AUTH_MAXFLAVOR;
	bool found_auth_null = false;
	unsigned int i;

	/*
	 * If the sec= mount option is used, the specified flavor or AUTH_NULL
	 * must be in the list returned by the server.
	 *
	 * AUTH_NULL has a special meaning when it's in the server list - it
	 * means that the server will ignore the rpc creds, so any flavor
	 * can be used but still use the sec= that was specified.
	 *
	 * Note also that the MNT procedure in MNTv1 does not return a list
	 * of supported security flavors. In this case, nfs_mount() fabricates
	 * a security flavor list containing just AUTH_NULL.
	 */
	for (i = 0; i < count; i++) {
		flavor = server_authlist[i];

		if (nfs_auth_info_match(&args->auth_info, flavor))
			goto out;

		if (flavor == RPC_AUTH_NULL)
			found_auth_null = true;
	}

	if (found_auth_null) {
		flavor = args->auth_info.flavors[0];
		goto out;
	}

	dfprintk(MOUNT,
		 "NFS: specified auth flavors not supported by server\n");
	return -EACCES;

out:
	args->selected_flavor = flavor;
	dfprintk(MOUNT, "NFS: using auth flavor %u\n", args->selected_flavor);
	return 0;
}