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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int kvm_make_vcpus_request_mask (struct kvm*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool kvm_make_all_cpus_request(struct kvm *kvm, unsigned int req)
{
	cpumask_var_t cpus;
	bool called;

	zalloc_cpumask_var(&cpus, GFP_ATOMIC);

	called = kvm_make_vcpus_request_mask(kvm, req, NULL, cpus);

	free_cpumask_var(cpus);
	return called;
}