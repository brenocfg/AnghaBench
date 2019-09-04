#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct TYPE_6__ {size_t mirror_array_cnt; TYPE_2__** mirror_array; } ;
struct TYPE_5__ {TYPE_1__* mirror_ds; } ;
struct TYPE_4__ {struct nfs4_deviceid_node id_node; } ;

/* Variables and functions */
 TYPE_3__* FF_LAYOUT_LSEG (struct pnfs_layout_segment*) ; 

__attribute__((used)) static inline struct nfs4_deviceid_node *
FF_LAYOUT_DEVID_NODE(struct pnfs_layout_segment *lseg, u32 idx)
{
	if (idx >= FF_LAYOUT_LSEG(lseg)->mirror_array_cnt ||
	    FF_LAYOUT_LSEG(lseg)->mirror_array[idx] == NULL ||
	    FF_LAYOUT_LSEG(lseg)->mirror_array[idx]->mirror_ds == NULL)
		return NULL;
	return &FF_LAYOUT_LSEG(lseg)->mirror_array[idx]->mirror_ds->id_node;
}