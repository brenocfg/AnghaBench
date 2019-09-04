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
typedef  void* u8 ;
typedef  int u32 ;
struct usbduxsigma_private {int* dux_commands; int /*<<< orphan*/  mut; scalar_t__ insn_buf; scalar_t__ ai_cmd_running; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  USBDUXSIGMA_SINGLE_AD_CMD ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  create_adc_command (unsigned int,void**,void**) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usbbuxsigma_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int usbduxsigma_receive_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsigma_ai_insn_read(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	struct usbduxsigma_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	u8 muxsg0 = 0;
	u8 muxsg1 = 0;
	u8 sysred = 0;
	int ret;
	int i;

	mutex_lock(&devpriv->mut);
	if (devpriv->ai_cmd_running) {
		mutex_unlock(&devpriv->mut);
		return -EBUSY;
	}

	create_adc_command(chan, &muxsg0, &muxsg1);

	/* Mode 0 is used to get a single conversion on demand */
	devpriv->dux_commands[1] = 0x16; /* CONFIG0: chopper on */
	devpriv->dux_commands[2] = 0x80; /* CONFIG1: 2kHz sampling rate */
	devpriv->dux_commands[3] = 0x00; /* CONFIG3: diff. channels off */
	devpriv->dux_commands[4] = muxsg0;
	devpriv->dux_commands[5] = muxsg1;
	devpriv->dux_commands[6] = sysred;

	/* adc commands */
	ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
	if (ret < 0) {
		mutex_unlock(&devpriv->mut);
		return ret;
	}

	for (i = 0; i < insn->n; i++) {
		u32 val;

		ret = usbduxsigma_receive_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
		if (ret < 0) {
			mutex_unlock(&devpriv->mut);
			return ret;
		}

		/* 32 bits big endian from the A/D converter */
		val = be32_to_cpu(get_unaligned((__be32
						 *)(devpriv->insn_buf + 1)));
		val &= 0x00ffffff;	/* strip status byte */
		data[i] = comedi_offset_munge(s, val);
	}
	mutex_unlock(&devpriv->mut);

	return insn->n;
}