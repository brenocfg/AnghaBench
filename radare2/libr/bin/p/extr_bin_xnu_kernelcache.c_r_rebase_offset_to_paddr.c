#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct section_t {scalar_t__ addr; scalar_t__ vsize; scalar_t__ offset; int /*<<< orphan*/  last; } ;
struct TYPE_5__ {TYPE_1__* rebase_info; } ;
struct TYPE_4__ {scalar_t__ kernel_base; } ;
typedef  TYPE_2__ RKernelCacheObj ;

/* Variables and functions */

__attribute__((used)) static ut64 r_rebase_offset_to_paddr (RKernelCacheObj *obj, struct section_t *sections, ut64 offset) {
	ut64 vaddr = obj->rebase_info->kernel_base + offset;
	int i = 0;
	for (; !sections[i].last; i++) {
		if (sections[i].addr <= vaddr && vaddr < (sections[i].addr + sections[i].vsize)) {
			return sections[i].offset + (vaddr - sections[i].addr);
		}
	}
	return offset;
}