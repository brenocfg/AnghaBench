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
 scalar_t__ local_page ; 
 scalar_t__ local_size ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  mach_vm_deallocate (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ target_page_base ; 

__attribute__((used)) static void fpm_mach_vm_deallocate() /* {{{ */
{
	if (local_page) {
		mach_vm_deallocate(mach_task_self(), local_page, local_size);
		target_page_base = 0;
		local_page = 0;
		local_size = 0;
	}
}