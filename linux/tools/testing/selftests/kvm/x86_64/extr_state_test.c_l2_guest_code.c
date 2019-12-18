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
 int /*<<< orphan*/  GUEST_ASSERT (int) ; 
 int /*<<< orphan*/  GUEST_RIP ; 
 int /*<<< orphan*/  GUEST_SYNC (int) ; 
 int /*<<< orphan*/  vmcall () ; 
 int vmreadz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmwrite (int /*<<< orphan*/ ,int) ; 

void l2_guest_code(void)
{
	GUEST_SYNC(6);

        /* Exit to L1 */
	vmcall();

	/* L1 has now set up a shadow VMCS for us.  */
	GUEST_ASSERT(vmreadz(GUEST_RIP) == 0xc0ffee);
	GUEST_SYNC(10);
	GUEST_ASSERT(vmreadz(GUEST_RIP) == 0xc0ffee);
	GUEST_ASSERT(!vmwrite(GUEST_RIP, 0xc0fffee));
	GUEST_SYNC(11);
	GUEST_ASSERT(vmreadz(GUEST_RIP) == 0xc0fffee);
	GUEST_ASSERT(!vmwrite(GUEST_RIP, 0xc0ffffee));
	GUEST_SYNC(12);

	/* Done, exit to L1 and never come back.  */
	vmcall();
}