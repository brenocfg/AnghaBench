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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char MCT_U232_MSR_CD ; 
 unsigned char MCT_U232_MSR_CTS ; 
 unsigned char MCT_U232_MSR_DSR ; 
 unsigned char MCT_U232_MSR_RI ; 
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,unsigned int) ; 

__attribute__((used)) static void mct_u232_msr_to_state(struct usb_serial_port *port,
				  unsigned int *control_state, unsigned char msr)
{
	/* Translate Control Line states */
	if (msr & MCT_U232_MSR_DSR)
		*control_state |=  TIOCM_DSR;
	else
		*control_state &= ~TIOCM_DSR;
	if (msr & MCT_U232_MSR_CTS)
		*control_state |=  TIOCM_CTS;
	else
		*control_state &= ~TIOCM_CTS;
	if (msr & MCT_U232_MSR_RI)
		*control_state |=  TIOCM_RI;
	else
		*control_state &= ~TIOCM_RI;
	if (msr & MCT_U232_MSR_CD)
		*control_state |=  TIOCM_CD;
	else
		*control_state &= ~TIOCM_CD;
	dev_dbg(&port->dev, "msr_to_state: msr=0x%x ==> state=0x%x\n", msr, *control_state);
}