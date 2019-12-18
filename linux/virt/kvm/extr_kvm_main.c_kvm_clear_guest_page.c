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
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZERO_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 int kvm_write_guest_page (struct kvm*,int /*<<< orphan*/ ,void const*,int,int) ; 
 int /*<<< orphan*/  page_to_phys (int /*<<< orphan*/ ) ; 

int kvm_clear_guest_page(struct kvm *kvm, gfn_t gfn, int offset, int len)
{
	const void *zero_page = (const void *) __va(page_to_phys(ZERO_PAGE(0)));

	return kvm_write_guest_page(kvm, gfn, zero_page, offset, len);
}