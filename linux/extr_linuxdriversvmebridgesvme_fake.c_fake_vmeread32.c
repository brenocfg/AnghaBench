#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct fake_driver {TYPE_1__* slaves; } ;
struct TYPE_2__ {scalar_t__ aspace; scalar_t__ cycle; unsigned long long vme_base; unsigned long long size; scalar_t__ buf_base; } ;

/* Variables and functions */
 int FAKE_MAX_SLAVE ; 
 int /*<<< orphan*/  fake_lm_check (struct fake_driver*,unsigned long long,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 fake_vmeread32(struct fake_driver *bridge, unsigned long long addr,
		u32 aspace, u32 cycle)
{
	u32 retval = 0xffffffff;
	int i;
	unsigned long long start, end, offset;
	u32 *loc;

	for (i = 0; i < FAKE_MAX_SLAVE; i++) {
		if (aspace != bridge->slaves[i].aspace)
			continue;

		if (cycle != bridge->slaves[i].cycle)
			continue;

		start = bridge->slaves[i].vme_base;
		end = bridge->slaves[i].vme_base + bridge->slaves[i].size;

		if ((addr >= start) && ((addr + 3) < end)) {
			offset = addr - bridge->slaves[i].vme_base;
			loc = (u32 *)(bridge->slaves[i].buf_base + offset);
			retval = *loc;

			break;
		}
	}

	fake_lm_check(bridge, addr, aspace, cycle);

	return retval;
}