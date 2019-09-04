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
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ENDPTCOMPLETE ; 
 int /*<<< orphan*/  OP_ENDPTFLUSH ; 
 int /*<<< orphan*/  OP_ENDPTPRIME ; 
 int /*<<< orphan*/  OP_ENDPTSETUPSTAT ; 
 scalar_t__ hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_usb_set_address (struct ci_hdrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hw_usb_reset(struct ci_hdrc *ci)
{
	hw_usb_set_address(ci, 0);

	/* ESS flushes only at end?!? */
	hw_write(ci, OP_ENDPTFLUSH,    ~0, ~0);

	/* clear setup token semaphores */
	hw_write(ci, OP_ENDPTSETUPSTAT, 0,  0);

	/* clear complete status */
	hw_write(ci, OP_ENDPTCOMPLETE,  0,  0);

	/* wait until all bits cleared */
	while (hw_read(ci, OP_ENDPTPRIME, ~0))
		udelay(10);             /* not RTOS friendly */

	/* reset all endpoints ? */

	/* reset internal status and wait for further instructions
	   no need to verify the port reset status (ESS does it) */

	return 0;
}