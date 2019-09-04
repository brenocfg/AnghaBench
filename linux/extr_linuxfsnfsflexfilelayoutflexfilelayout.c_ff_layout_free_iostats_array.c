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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct nfs42_layoutstat_devinfo {TYPE_2__ ld_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
ff_layout_free_iostats_array(struct nfs42_layoutstat_devinfo *devinfo,
		unsigned int num_entries)
{
	unsigned int i;

	for (i = 0; i < num_entries; i++) {
		if (!devinfo[i].ld_private.ops)
			continue;
		if (!devinfo[i].ld_private.ops->free)
			continue;
		devinfo[i].ld_private.ops->free(&devinfo[i].ld_private);
	}
}