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
struct uprobe_dispatch_data {unsigned long bp_addr; TYPE_2__* tu; } ;
struct TYPE_6__ {TYPE_1__* utask; } ;
struct TYPE_5__ {unsigned long offset; } ;
struct TYPE_4__ {scalar_t__ vaddr; } ;

/* Variables and functions */
 TYPE_3__* current ; 

__attribute__((used)) static unsigned long translate_user_vaddr(void *file_offset)
{
	unsigned long base_addr;
	struct uprobe_dispatch_data *udd;

	udd = (void *) current->utask->vaddr;

	base_addr = udd->bp_addr - udd->tu->offset;
	return base_addr + (unsigned long)file_offset;
}