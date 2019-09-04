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
typedef  size_t u8 ;
typedef  int u32 ;
struct s626_private {size_t* trim_setpoint; } ;
struct comedi_device {scalar_t__ mmio; struct s626_private* private; } ;

/* Variables and functions */
 int S626_EOS ; 
 scalar_t__ S626_VECTPORT (int) ; 
 int S626_WS1 ; 
 int S626_WS3 ; 
 int S626_XFIFO_0 ; 
 int S626_XFIFO_1 ; 
 int S626_XFIFO_2 ; 
 int S626_XFIFO_3 ; 
 int S626_XSD2 ; 
 int s626_send_dac (struct comedi_device*,int) ; 
 int* s626_trimchan ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s626_write_trim_dac(struct comedi_device *dev,
			       u8 logical_chan, u8 dac_data)
{
	struct s626_private *devpriv = dev->private;
	u32 chan;

	/*
	 * Save the new setpoint in case the application needs to read it back
	 * later.
	 */
	devpriv->trim_setpoint[logical_chan] = dac_data;

	/* Map logical channel number to physical channel number. */
	chan = s626_trimchan[logical_chan];

	/*
	 * Set up TSL2 records for TrimDac write operation.  All slots shift
	 * 0xFF in from pulled-up SD3 so that the end of the slot sequence
	 * can be detected.
	 */

	/* Slot 2: Send high uint8_t to target TrimDac */
	writel(S626_XSD2 | S626_XFIFO_1 | S626_WS3,
	       dev->mmio + S626_VECTPORT(2));
	/* Slot 3: Send low uint8_t to target TrimDac */
	writel(S626_XSD2 | S626_XFIFO_0 | S626_WS3,
	       dev->mmio + S626_VECTPORT(3));
	/* Slot 4: Send NOP high uint8_t to DAC0 to keep clock running */
	writel(S626_XSD2 | S626_XFIFO_3 | S626_WS1,
	       dev->mmio + S626_VECTPORT(4));
	/* Slot 5: Send NOP low  uint8_t to DAC0 */
	writel(S626_XSD2 | S626_XFIFO_2 | S626_WS1 | S626_EOS,
	       dev->mmio + S626_VECTPORT(5));

	/*
	 * Construct and transmit target DAC's serial packet:
	 * (0000 AAAA), (DDDD DDDD), (0x00), (0x00) where A<3:0> is the
	 * DAC channel's address, and D<7:0> is the DAC setpoint.  Append a
	 * WORD value (that writes a channel 0 NOP command to a non-existent
	 * main DAC channel) that serves to keep the clock running after the
	 * packet has been sent to the target DAC.
	 */

	/*
	 * Address the DAC channel within the trimdac device.
	 * Include DAC setpoint data.
	 */
	return s626_send_dac(dev, (chan << 8) | dac_data);
}