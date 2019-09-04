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
struct vmx_pages {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_DONE () ; 
 int /*<<< orphan*/  GUEST_SYNC (int) ; 
 int /*<<< orphan*/  l1_guest_code (struct vmx_pages*) ; 

void guest_code(struct vmx_pages *vmx_pages)
{
	GUEST_SYNC(1);
	GUEST_SYNC(2);

	if (vmx_pages)
		l1_guest_code(vmx_pages);

	GUEST_DONE();
}