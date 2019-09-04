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
struct kvm_vcpu {int dummy; } ;
struct kvm_io_range {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct kvm_io_bus {int dev_count; TYPE_1__* range; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ kvm_io_bus_cmp (struct kvm_io_range*,TYPE_1__*) ; 
 int kvm_io_bus_get_first_dev (struct kvm_io_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_iodevice_read (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int __kvm_io_bus_read(struct kvm_vcpu *vcpu, struct kvm_io_bus *bus,
			     struct kvm_io_range *range, void *val)
{
	int idx;

	idx = kvm_io_bus_get_first_dev(bus, range->addr, range->len);
	if (idx < 0)
		return -EOPNOTSUPP;

	while (idx < bus->dev_count &&
		kvm_io_bus_cmp(range, &bus->range[idx]) == 0) {
		if (!kvm_iodevice_read(vcpu, bus->range[idx].dev, range->addr,
				       range->len, val))
			return idx;
		idx++;
	}

	return -EOPNOTSUPP;
}