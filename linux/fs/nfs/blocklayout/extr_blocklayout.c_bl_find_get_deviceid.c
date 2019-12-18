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
struct nfs4_deviceid_node {int /*<<< orphan*/  nfs_client; int /*<<< orphan*/  ld; int /*<<< orphan*/  timestamp_unavailable; int /*<<< orphan*/  flags; } ;
struct nfs4_deviceid {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct nfs4_deviceid_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_DEVICEID_UNAVAILABLE ; 
 unsigned long PNFS_DEVICE_RETRY_TIMEOUT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  nfs4_delete_deviceid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs4_deviceid const*) ; 
 struct nfs4_deviceid_node* nfs4_find_get_deviceid (struct nfs_server*,struct nfs4_deviceid const*,struct cred const*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_in_range (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static struct nfs4_deviceid_node *
bl_find_get_deviceid(struct nfs_server *server,
		const struct nfs4_deviceid *id, const struct cred *cred,
		gfp_t gfp_mask)
{
	struct nfs4_deviceid_node *node;
	unsigned long start, end;

retry:
	node = nfs4_find_get_deviceid(server, id, cred, gfp_mask);
	if (!node)
		return ERR_PTR(-ENODEV);

	if (test_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags) == 0)
		return node;

	end = jiffies;
	start = end - PNFS_DEVICE_RETRY_TIMEOUT;
	if (!time_in_range(node->timestamp_unavailable, start, end)) {
		nfs4_delete_deviceid(node->ld, node->nfs_client, id);
		goto retry;
	}
	return ERR_PTR(-ENODEV);
}