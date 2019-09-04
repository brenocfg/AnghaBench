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
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;

/* Variables and functions */
 struct nfs4_deviceid_node* FF_LAYOUT_DEVID_NODE (struct pnfs_layout_segment*,int) ; 
 int ff_layout_test_devid_unavailable (struct nfs4_deviceid_node*) ; 

__attribute__((used)) static bool
ff_layout_device_unavailable(struct pnfs_layout_segment *lseg, int idx)
{
	/* No mirroring for now */
	struct nfs4_deviceid_node *node = FF_LAYOUT_DEVID_NODE(lseg, idx);

	return ff_layout_test_devid_unavailable(node);
}