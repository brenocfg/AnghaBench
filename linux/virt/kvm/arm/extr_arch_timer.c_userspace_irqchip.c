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

/* Variables and functions */
 int /*<<< orphan*/  irqchip_in_kernel (struct kvm*) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  userspace_irqchip_in_use ; 

__attribute__((used)) static inline bool userspace_irqchip(struct kvm *kvm)
{
	return static_branch_unlikely(&userspace_irqchip_in_use) &&
		unlikely(!irqchip_in_kernel(kvm));
}