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
struct pnfs_device {int dummy; } ;
struct nfs_server {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct nfs4_file_layout_dsaddr {struct nfs4_deviceid_node id_node; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct nfs4_file_layout_dsaddr* nfs4_fl_alloc_deviceid_node (struct nfs_server*,struct pnfs_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_deviceid_node *
filelayout_alloc_deviceid_node(struct nfs_server *server,
		struct pnfs_device *pdev, gfp_t gfp_flags)
{
	struct nfs4_file_layout_dsaddr *dsaddr;

	dsaddr = nfs4_fl_alloc_deviceid_node(server, pdev, gfp_flags);
	if (!dsaddr)
		return NULL;
	return &dsaddr->id_node;
}