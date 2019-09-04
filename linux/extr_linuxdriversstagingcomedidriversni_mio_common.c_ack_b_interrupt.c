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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned short NISTC_AO_STATUS1_BC_TC ; 
 unsigned short NISTC_AO_STATUS1_OVERRUN ; 
 unsigned short NISTC_AO_STATUS1_START ; 
 unsigned short NISTC_AO_STATUS1_START1 ; 
 unsigned short NISTC_AO_STATUS1_UC_TC ; 
 unsigned short NISTC_AO_STATUS1_UI2_TC ; 
 unsigned short NISTC_AO_STATUS1_UPDATE ; 
 unsigned short NISTC_INTB_ACK_AO_BC_TC ; 
 unsigned short NISTC_INTB_ACK_AO_ERR ; 
 unsigned short NISTC_INTB_ACK_AO_START ; 
 unsigned short NISTC_INTB_ACK_AO_START1 ; 
 unsigned short NISTC_INTB_ACK_AO_UC_TC ; 
 unsigned short NISTC_INTB_ACK_AO_UI2_TC ; 
 unsigned short NISTC_INTB_ACK_AO_UPDATE ; 
 int /*<<< orphan*/  NISTC_INTB_ACK_REG ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ack_b_interrupt(struct comedi_device *dev, unsigned short b_status)
{
	unsigned short ack = 0;

	if (b_status & NISTC_AO_STATUS1_BC_TC)
		ack |= NISTC_INTB_ACK_AO_BC_TC;
	if (b_status & NISTC_AO_STATUS1_OVERRUN)
		ack |= NISTC_INTB_ACK_AO_ERR;
	if (b_status & NISTC_AO_STATUS1_START)
		ack |= NISTC_INTB_ACK_AO_START;
	if (b_status & NISTC_AO_STATUS1_START1)
		ack |= NISTC_INTB_ACK_AO_START1;
	if (b_status & NISTC_AO_STATUS1_UC_TC)
		ack |= NISTC_INTB_ACK_AO_UC_TC;
	if (b_status & NISTC_AO_STATUS1_UI2_TC)
		ack |= NISTC_INTB_ACK_AO_UI2_TC;
	if (b_status & NISTC_AO_STATUS1_UPDATE)
		ack |= NISTC_INTB_ACK_AO_UPDATE;
	if (ack)
		ni_stc_writew(dev, ack, NISTC_INTB_ACK_REG);
}