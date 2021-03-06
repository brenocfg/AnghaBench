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
struct kvm_sync_regs {int dummy; } ;
struct kvm_sregs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_COMPARE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acrs ; 
 int /*<<< orphan*/ * crs ; 

__attribute__((used)) static void compare_sregs(struct kvm_sregs *left, struct kvm_sync_regs *right)
{
	int i;

	for (i = 0; i < 16; i++)
		REG_COMPARE(acrs[i]);

	for (i = 0; i < 16; i++)
		REG_COMPARE(crs[i]);
}