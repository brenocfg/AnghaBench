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
typedef  int /*<<< orphan*/  uint64_t ;
struct kvm_vm {int dummy; } ;
typedef  enum vm_guest_mode { ____Placeholder_vm_guest_mode } vm_guest_mode ;

/* Variables and functions */
 struct kvm_vm* _vm_create (int,int /*<<< orphan*/ ,int) ; 

struct kvm_vm *vm_create(enum vm_guest_mode mode, uint64_t phy_pages, int perm)
{
	return _vm_create(mode, phy_pages, perm);
}