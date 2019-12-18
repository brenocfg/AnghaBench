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
struct kvm_io_range {scalar_t__ addr; scalar_t__ len; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */

__attribute__((used)) static inline int kvm_io_bus_cmp(const struct kvm_io_range *r1,
				 const struct kvm_io_range *r2)
{
	gpa_t addr1 = r1->addr;
	gpa_t addr2 = r2->addr;

	if (addr1 < addr2)
		return -1;

	/* If r2->len == 0, match the exact address.  If r2->len != 0,
	 * accept any overlapping write.  Any order is acceptable for
	 * overlapping ranges, because kvm_io_bus_get_first_dev ensures
	 * we process all of them.
	 */
	if (r2->len) {
		addr1 += r1->len;
		addr2 += r2->len;
	}

	if (addr1 > addr2)
		return 1;

	return 0;
}