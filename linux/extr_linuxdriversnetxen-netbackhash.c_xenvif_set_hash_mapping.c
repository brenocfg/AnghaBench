#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int** mapping; size_t mapping_sel; int size; } ;
struct xenvif {int num_queues; TYPE_5__ hash; int /*<<< orphan*/  domid; } ;
struct TYPE_6__ {int ref; } ;
struct TYPE_9__ {int offset; int /*<<< orphan*/  domid; TYPE_1__ u; } ;
struct TYPE_7__ {void* gmfn; } ;
struct TYPE_8__ {int offset; TYPE_2__ u; int /*<<< orphan*/  domid; } ;
struct gnttab_copy {int len; scalar_t__ status; TYPE_4__ source; TYPE_3__ dest; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  GNTCOPY_source_gref ; 
 scalar_t__ GNTST_okay ; 
 int XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER ; 
 int XEN_NETIF_CTRL_STATUS_SUCCESS ; 
 int XEN_PAGE_SIZE ; 
 int /*<<< orphan*/  gnttab_batch_copy (struct gnttab_copy*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 void* virt_to_gfn (int*) ; 
 int xen_offset_in_page (int*) ; 

u32 xenvif_set_hash_mapping(struct xenvif *vif, u32 gref, u32 len,
			    u32 off)
{
	u32 *mapping = vif->hash.mapping[!vif->hash.mapping_sel];
	unsigned int nr = 1;
	struct gnttab_copy copy_op[2] = {{
		.source.u.ref = gref,
		.source.domid = vif->domid,
		.dest.domid = DOMID_SELF,
		.len = len * sizeof(*mapping),
		.flags = GNTCOPY_source_gref
	}};

	if ((off + len < off) || (off + len > vif->hash.size) ||
	    len > XEN_PAGE_SIZE / sizeof(*mapping))
		return XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	copy_op[0].dest.u.gmfn = virt_to_gfn(mapping + off);
	copy_op[0].dest.offset = xen_offset_in_page(mapping + off);
	if (copy_op[0].dest.offset + copy_op[0].len > XEN_PAGE_SIZE) {
		copy_op[1] = copy_op[0];
		copy_op[1].source.offset = XEN_PAGE_SIZE - copy_op[0].dest.offset;
		copy_op[1].dest.u.gmfn = virt_to_gfn(mapping + off + len);
		copy_op[1].dest.offset = 0;
		copy_op[1].len = copy_op[0].len - copy_op[1].source.offset;
		copy_op[0].len = copy_op[1].source.offset;
		nr = 2;
	}

	memcpy(mapping, vif->hash.mapping[vif->hash.mapping_sel],
	       vif->hash.size * sizeof(*mapping));

	if (copy_op[0].len != 0) {
		gnttab_batch_copy(copy_op, nr);

		if (copy_op[0].status != GNTST_okay ||
		    copy_op[nr - 1].status != GNTST_okay)
			return XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;
	}

	while (len-- != 0)
		if (mapping[off++] >= vif->num_queues)
			return XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	vif->hash.mapping_sel = !vif->hash.mapping_sel;

	return XEN_NETIF_CTRL_STATUS_SUCCESS;
}