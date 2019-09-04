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
typedef  int u32 ;
typedef  int u16 ;
struct s626_private {int dacpol; } ;
struct comedi_device {scalar_t__ mmio; struct s626_private* private; } ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int S626_EOS ; 
 scalar_t__ S626_VECTPORT (int) ; 
 int S626_WS1 ; 
 int S626_WS2 ; 
 int S626_WS3 ; 
 int S626_XFIFO_0 ; 
 int S626_XFIFO_1 ; 
 int S626_XFIFO_2 ; 
 int S626_XFIFO_3 ; 
 int S626_XSD2 ; 
 int s626_send_dac (struct comedi_device*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s626_set_dac(struct comedi_device *dev,
			u16 chan, int16_t dacdata)
{
	struct s626_private *devpriv = dev->private;
	u16 signmask;
	u32 ws_image;
	u32 val;

	/*
	 * Adjust DAC data polarity and set up Polarity Control Register image.
	 */
	signmask = 1 << chan;
	if (dacdata < 0) {
		dacdata = -dacdata;
		devpriv->dacpol |= signmask;
	} else {
		devpriv->dacpol &= ~signmask;
	}

	/* Limit DAC setpoint value to valid range. */
	if ((u16)dacdata > 0x1FFF)
		dacdata = 0x1FFF;

	/*
	 * Set up TSL2 records (aka "vectors") for DAC update.  Vectors V2
	 * and V3 transmit the setpoint to the target DAC.  V4 and V5 send
	 * data to a non-existent TrimDac channel just to keep the clock
	 * running after sending data to the target DAC.  This is necessary
	 * to eliminate the clock glitch that would otherwise occur at the
	 * end of the target DAC's serial data stream.  When the sequence
	 * restarts at V0 (after executing V5), the gate array automatically
	 * disables gating for the DAC clock and all DAC chip selects.
	 */

	/* Choose DAC chip select to be asserted */
	ws_image = (chan & 2) ? S626_WS1 : S626_WS2;
	/* Slot 2: Transmit high data byte to target DAC */
	writel(S626_XSD2 | S626_XFIFO_1 | ws_image,
	       dev->mmio + S626_VECTPORT(2));
	/* Slot 3: Transmit low data byte to target DAC */
	writel(S626_XSD2 | S626_XFIFO_0 | ws_image,
	       dev->mmio + S626_VECTPORT(3));
	/* Slot 4: Transmit to non-existent TrimDac channel to keep clock */
	writel(S626_XSD2 | S626_XFIFO_3 | S626_WS3,
	       dev->mmio + S626_VECTPORT(4));
	/* Slot 5: running after writing target DAC's low data byte */
	writel(S626_XSD2 | S626_XFIFO_2 | S626_WS3 | S626_EOS,
	       dev->mmio + S626_VECTPORT(5));

	/*
	 * Construct and transmit target DAC's serial packet:
	 * (A10D DDDD), (DDDD DDDD), (0x0F), (0x00) where A is chan<0>,
	 * and D<12:0> is the DAC setpoint.  Append a WORD value (that writes
	 * to a  non-existent TrimDac channel) that serves to keep the clock
	 * running after the packet has been sent to the target DAC.
	 */
	val = 0x0F000000;	/* Continue clock after target DAC data
				 * (write to non-existent trimdac).
				 */
	val |= 0x00004000;	/* Address the two main dual-DAC devices
				 * (TSL's chip select enables target device).
				 */
	val |= ((u32)(chan & 1) << 15);	/* Address the DAC channel
					 * within the device.
					 */
	val |= (u32)dacdata;	/* Include DAC setpoint data. */
	return s626_send_dac(dev, val);
}