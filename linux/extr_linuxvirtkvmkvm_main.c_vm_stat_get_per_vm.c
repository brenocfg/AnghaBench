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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u64 ;
struct kvm_stat_data {int offset; scalar_t__ kvm; } ;

/* Variables and functions */

__attribute__((used)) static int vm_stat_get_per_vm(void *data, u64 *val)
{
	struct kvm_stat_data *stat_data = (struct kvm_stat_data *)data;

	*val = *(ulong *)((void *)stat_data->kvm + stat_data->offset);

	return 0;
}