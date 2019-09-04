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
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct TYPE_6__ {TYPE_2__* mirror_ds; } ;
struct TYPE_5__ {TYPE_1__* ds_versions; } ;
struct TYPE_4__ {int version; } ;

/* Variables and functions */
 TYPE_3__* FF_LAYOUT_COMP (struct pnfs_layout_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
nfs4_ff_layout_ds_version(struct pnfs_layout_segment *lseg, u32 ds_idx)
{
	return FF_LAYOUT_COMP(lseg, ds_idx)->mirror_ds->ds_versions[0].version;
}