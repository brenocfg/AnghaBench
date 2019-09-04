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
typedef  int /*<<< orphan*/  u64 ;
struct nvdimm_bus {int /*<<< orphan*/  badrange; } ;

/* Variables and functions */
 int badrange_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nvdimm_bus_add_badrange(struct nvdimm_bus *nvdimm_bus, u64 addr, u64 length)
{
	return badrange_add(&nvdimm_bus->badrange, addr, length);
}