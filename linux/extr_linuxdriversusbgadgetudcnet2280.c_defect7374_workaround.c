#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_ctrlrequest {int bRequestType; } ;
struct net2280 {int bug7734_patched; int /*<<< orphan*/  regs; TYPE_2__* plregs; TYPE_1__* usb; } ;
struct TYPE_4__ {int /*<<< orphan*/  pl_ep_status_1; } ;
struct TYPE_3__ {int /*<<< orphan*/  usbstat; } ;

/* Variables and functions */
 int ACK_GOOD_MORE_ACKS_TO_COME ; 
 int ACK_GOOD_NORMAL ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int DEFECT7374_FSM_FIELD ; 
 int DEFECT7374_FSM_NON_SS_CONTROL_READ ; 
 int DEFECT7374_FSM_SS_CONTROL_READ ; 
 int DEFECT7374_FSM_WAITING_FOR_CONTROL_READ ; 
 int DEFECT_7374_NUMBEROF_MAX_WAIT_LOOPS ; 
 int DEFECT_7374_PROCESSOR_WAIT_TIME ; 
 int /*<<< orphan*/  SCRATCH ; 
 int STATE ; 
 int /*<<< orphan*/  SUPER_SPEED_MODE ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  defect7374_disable_data_eps (struct net2280*) ; 
 int /*<<< orphan*/  ep_err (struct net2280*,char*,...) ; 
 int /*<<< orphan*/  ep_warn (struct net2280*,char*,int) ; 
 int get_idx_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_idx_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void defect7374_workaround(struct net2280 *dev, struct usb_ctrlrequest r)
{
	u32 scratch, fsmvalue;
	u32 ack_wait_timeout, state;

	/* Workaround for Defect 7374 (U1/U2 erroneously rejected): */
	scratch = get_idx_reg(dev->regs, SCRATCH);
	fsmvalue = scratch & (0xf << DEFECT7374_FSM_FIELD);
	scratch &= ~(0xf << DEFECT7374_FSM_FIELD);

	if (!((fsmvalue == DEFECT7374_FSM_WAITING_FOR_CONTROL_READ) &&
				(r.bRequestType & USB_DIR_IN)))
		return;

	/* This is the first Control Read for this connection: */
	if (!(readl(&dev->usb->usbstat) & BIT(SUPER_SPEED_MODE))) {
		/*
		 * Connection is NOT SS:
		 * - Connection must be FS or HS.
		 * - This FSM state should allow workaround software to
		 * run after the next USB connection.
		 */
		scratch |= DEFECT7374_FSM_NON_SS_CONTROL_READ;
		dev->bug7734_patched = 1;
		goto restore_data_eps;
	}

	/* Connection is SS: */
	for (ack_wait_timeout = 0;
			ack_wait_timeout < DEFECT_7374_NUMBEROF_MAX_WAIT_LOOPS;
			ack_wait_timeout++) {

		state =	readl(&dev->plregs->pl_ep_status_1)
			& (0xff << STATE);
		if ((state >= (ACK_GOOD_NORMAL << STATE)) &&
			(state <= (ACK_GOOD_MORE_ACKS_TO_COME << STATE))) {
			scratch |= DEFECT7374_FSM_SS_CONTROL_READ;
			dev->bug7734_patched = 1;
			break;
		}

		/*
		 * We have not yet received host's Data Phase ACK
		 * - Wait and try again.
		 */
		udelay(DEFECT_7374_PROCESSOR_WAIT_TIME);

		continue;
	}


	if (ack_wait_timeout >= DEFECT_7374_NUMBEROF_MAX_WAIT_LOOPS) {
		ep_err(dev, "FAIL: Defect 7374 workaround waited but failed "
		"to detect SS host's data phase ACK.");
		ep_err(dev, "PL_EP_STATUS_1(23:16):.Expected from 0x11 to 0x16"
		"got 0x%2.2x.\n", state >> STATE);
	} else {
		ep_warn(dev, "INFO: Defect 7374 workaround waited about\n"
		"%duSec for Control Read Data Phase ACK\n",
			DEFECT_7374_PROCESSOR_WAIT_TIME * ack_wait_timeout);
	}

restore_data_eps:
	/*
	 * Restore data EPs to their pre-workaround settings (disabled,
	 * initialized, and other details).
	 */
	defect7374_disable_data_eps(dev);

	set_idx_reg(dev->regs, SCRATCH, scratch);

	return;
}