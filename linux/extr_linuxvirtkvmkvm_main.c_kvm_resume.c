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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardware_enable_nolock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_count_lock ; 
 scalar_t__ kvm_usage_count ; 
 int /*<<< orphan*/  raw_spin_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_resume(void)
{
	if (kvm_usage_count) {
		WARN_ON(raw_spin_is_locked(&kvm_count_lock));
		hardware_enable_nolock(NULL);
	}
}