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
 int /*<<< orphan*/  hardware_disable_nolock (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_usage_count ; 

__attribute__((used)) static int kvm_suspend(void)
{
	if (kvm_usage_count)
		hardware_disable_nolock(NULL);
	return 0;
}