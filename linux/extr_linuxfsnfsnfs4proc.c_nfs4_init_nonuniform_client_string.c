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
struct nfs_client {char* cl_owner_id; TYPE_1__* cl_rpcclient; } ;
struct TYPE_2__ {char* cl_nodename; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  RPC_DISPLAY_ADDR ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 char* nfs4_client_id_uniquifier ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 char* rpc_peeraddr2str (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
nfs4_init_nonuniform_client_string(struct nfs_client *clp)
{
	size_t len;
	char *str;

	if (clp->cl_owner_id != NULL)
		return 0;

	rcu_read_lock();
	len = 14 +
		strlen(clp->cl_rpcclient->cl_nodename) +
		1 +
		strlen(rpc_peeraddr2str(clp->cl_rpcclient, RPC_DISPLAY_ADDR)) +
		1;
	rcu_read_unlock();
	if (nfs4_client_id_uniquifier[0] != '\0')
		len += strlen(nfs4_client_id_uniquifier) + 1;
	if (len > NFS4_OPAQUE_LIMIT + 1)
		return -EINVAL;

	/*
	 * Since this string is allocated at mount time, and held until the
	 * nfs_client is destroyed, we can use GFP_KERNEL here w/o worrying
	 * about a memory-reclaim deadlock.
	 */
	str = kmalloc(len, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	rcu_read_lock();
	if (nfs4_client_id_uniquifier[0] != '\0')
		scnprintf(str, len, "Linux NFSv4.0 %s/%s/%s",
			  clp->cl_rpcclient->cl_nodename,
			  nfs4_client_id_uniquifier,
			  rpc_peeraddr2str(clp->cl_rpcclient,
					   RPC_DISPLAY_ADDR));
	else
		scnprintf(str, len, "Linux NFSv4.0 %s/%s",
			  clp->cl_rpcclient->cl_nodename,
			  rpc_peeraddr2str(clp->cl_rpcclient,
					   RPC_DISPLAY_ADDR));
	rcu_read_unlock();

	clp->cl_owner_id = str;
	return 0;
}