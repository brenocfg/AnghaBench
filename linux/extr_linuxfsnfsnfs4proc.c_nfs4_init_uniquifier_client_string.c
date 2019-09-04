#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_client {char* cl_owner_id; TYPE_2__* cl_rpcclient; int /*<<< orphan*/  cl_minorversion; TYPE_1__* rpc_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_nodename; } ;
struct TYPE_3__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFS4_OPAQUE_LIMIT ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_client_id_uniquifier ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs4_init_uniquifier_client_string(struct nfs_client *clp)
{
	size_t len;
	char *str;

	len = 10 + 10 + 1 + 10 + 1 +
		strlen(nfs4_client_id_uniquifier) + 1 +
		strlen(clp->cl_rpcclient->cl_nodename) + 1;

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

	scnprintf(str, len, "Linux NFSv%u.%u %s/%s",
			clp->rpc_ops->version, clp->cl_minorversion,
			nfs4_client_id_uniquifier,
			clp->cl_rpcclient->cl_nodename);
	clp->cl_owner_id = str;
	return 0;
}