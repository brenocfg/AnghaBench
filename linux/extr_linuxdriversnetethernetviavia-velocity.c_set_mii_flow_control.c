#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flow_cntl; } ;
struct velocity_info {int /*<<< orphan*/  mac_regs; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISE_PAUSE_ASYM ; 
 int /*<<< orphan*/  ADVERTISE_PAUSE_CAP ; 
#define  FLOW_CNTL_DISABLE 131 
#define  FLOW_CNTL_RX 130 
#define  FLOW_CNTL_TX 129 
#define  FLOW_CNTL_TX_RX 128 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_REG_BITS_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_REG_BITS_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_mii_flow_control(struct velocity_info *vptr)
{
	/*Enable or Disable PAUSE in ANAR */
	switch (vptr->options.flow_cntl) {
	case FLOW_CNTL_TX:
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_ON(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		break;

	case FLOW_CNTL_RX:
		MII_REG_BITS_ON(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_ON(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		break;

	case FLOW_CNTL_TX_RX:
		MII_REG_BITS_ON(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		break;

	case FLOW_CNTL_DISABLE:
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_CAP, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_OFF(ADVERTISE_PAUSE_ASYM, MII_ADVERTISE, vptr->mac_regs);
		break;
	default:
		break;
	}
}