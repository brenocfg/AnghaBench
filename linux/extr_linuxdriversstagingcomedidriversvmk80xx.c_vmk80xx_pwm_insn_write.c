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
struct vmk80xx_private {unsigned char* usb_tx_buf; int /*<<< orphan*/  limit_sem; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int VMK8061_CMD_OUT_PWM ; 
 int VMK8061_PWM_REG1 ; 
 int VMK8061_PWM_REG2 ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 scalar_t__ vmk80xx_write_packet (struct comedi_device*,int) ; 

__attribute__((used)) static int vmk80xx_pwm_insn_write(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	struct vmk80xx_private *devpriv = dev->private;
	unsigned char *tx_buf;
	int reg[2];
	int cmd;
	int n;

	down(&devpriv->limit_sem);

	tx_buf = devpriv->usb_tx_buf;

	reg[0] = VMK8061_PWM_REG1;
	reg[1] = VMK8061_PWM_REG2;

	cmd = VMK8061_CMD_OUT_PWM;

	/*
	 * The followin piece of code was translated from the inline
	 * assembler code in the DLL source code.
	 *
	 * asm
	 *   mov eax, k  ; k is the value (data[n])
	 *   and al, 03h ; al are the lower 8 bits of eax
	 *   mov lo, al  ; lo is the low part (tx_buf[reg[0]])
	 *   mov eax, k
	 *   shr eax, 2  ; right shift eax register by 2
	 *   mov hi, al  ; hi is the high part (tx_buf[reg[1]])
	 * end;
	 */
	for (n = 0; n < insn->n; n++) {
		tx_buf[reg[0]] = (unsigned char)(data[n] & 0x03);
		tx_buf[reg[1]] = (unsigned char)(data[n] >> 2) & 0xff;

		if (vmk80xx_write_packet(dev, cmd))
			break;
	}

	up(&devpriv->limit_sem);

	return n;
}