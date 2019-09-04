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
typedef  int /*<<< orphan*/  u32 ;
struct s626_private {int /*<<< orphan*/ * dac_wbuf; int /*<<< orphan*/  dacpol; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; scalar_t__ mmio; struct s626_private* private; } ;

/* Variables and functions */
 int S626_EOS ; 
 int S626_ISR_AFOU ; 
 int /*<<< orphan*/  S626_LP_DACPOL ; 
 int /*<<< orphan*/  S626_MC1_A2OUT ; 
 scalar_t__ S626_P_FB_BUFFER2 ; 
 scalar_t__ S626_P_ISR ; 
 int /*<<< orphan*/  S626_P_MC1 ; 
 int S626_RSD2 ; 
 int S626_RSD3 ; 
 int S626_SIB_A2 ; 
 scalar_t__ S626_VECTPORT (int /*<<< orphan*/ ) ; 
 int S626_XFIFO_2 ; 
 int S626_XSD2 ; 
 int comedi_timeout (struct comedi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_mc_enable (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_send_dac_eoc ; 
 int /*<<< orphan*/  s626_send_dac_wait_fb_buffer2_msb_00 ; 
 int /*<<< orphan*/  s626_send_dac_wait_fb_buffer2_msb_ff ; 
 int /*<<< orphan*/  s626_send_dac_wait_not_mc1_a2out ; 
 int /*<<< orphan*/  s626_send_dac_wait_ssr_af2_out ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s626_send_dac(struct comedi_device *dev, u32 val)
{
	struct s626_private *devpriv = dev->private;
	int ret;

	/* START THE SERIAL CLOCK RUNNING ------------- */

	/*
	 * Assert DAC polarity control and enable gating of DAC serial clock
	 * and audio bit stream signals.  At this point in time we must be
	 * assured of being in time slot 0.  If we are not in slot 0, the
	 * serial clock and audio stream signals will be disabled; this is
	 * because the following s626_debi_write statement (which enables
	 * signals to be passed through the gate array) would execute before
	 * the trailing edge of WS1/WS3 (which turns off the signals), thus
	 * causing the signals to be inactive during the DAC write.
	 */
	s626_debi_write(dev, S626_LP_DACPOL, devpriv->dacpol);

	/* TRANSFER OUTPUT DWORD VALUE INTO A2'S OUTPUT FIFO ---------------- */

	/* Copy DAC setpoint value to DAC's output DMA buffer. */
	/* writel(val, dev->mmio + (uint32_t)devpriv->dac_wbuf); */
	*devpriv->dac_wbuf = val;

	/*
	 * Enable the output DMA transfer. This will cause the DMAC to copy
	 * the DAC's data value to A2's output FIFO. The DMA transfer will
	 * then immediately terminate because the protection address is
	 * reached upon transfer of the first DWORD value.
	 */
	s626_mc_enable(dev, S626_MC1_A2OUT, S626_P_MC1);

	/* While the DMA transfer is executing ... */

	/*
	 * Reset Audio2 output FIFO's underflow flag (along with any
	 * other FIFO underflow/overflow flags). When set, this flag
	 * will indicate that we have emerged from slot 0.
	 */
	writel(S626_ISR_AFOU, dev->mmio + S626_P_ISR);

	/*
	 * Wait for the DMA transfer to finish so that there will be data
	 * available in the FIFO when time slot 1 tries to transfer a DWORD
	 * from the FIFO to the output buffer register.  We test for DMA
	 * Done by polling the DMAC enable flag; this flag is automatically
	 * cleared when the transfer has finished.
	 */
	ret = comedi_timeout(dev, NULL, NULL, s626_send_dac_eoc,
			     s626_send_dac_wait_not_mc1_a2out);
	if (ret) {
		dev_err(dev->class_dev, "DMA transfer timeout\n");
		return ret;
	}

	/* START THE OUTPUT STREAM TO THE TARGET DAC -------------------- */

	/*
	 * FIFO data is now available, so we enable execution of time slots
	 * 1 and higher by clearing the EOS flag in slot 0.  Note that SD3
	 * will be shifted in and stored in FB_BUFFER2 for end-of-slot-list
	 * detection.
	 */
	writel(S626_XSD2 | S626_RSD3 | S626_SIB_A2,
	       dev->mmio + S626_VECTPORT(0));

	/*
	 * Wait for slot 1 to execute to ensure that the Packet will be
	 * transmitted.  This is detected by polling the Audio2 output FIFO
	 * underflow flag, which will be set when slot 1 execution has
	 * finished transferring the DAC's data DWORD from the output FIFO
	 * to the output buffer register.
	 */
	ret = comedi_timeout(dev, NULL, NULL, s626_send_dac_eoc,
			     s626_send_dac_wait_ssr_af2_out);
	if (ret) {
		dev_err(dev->class_dev,
			"TSL timeout waiting for slot 1 to execute\n");
		return ret;
	}

	/*
	 * Set up to trap execution at slot 0 when the TSL sequencer cycles
	 * back to slot 0 after executing the EOS in slot 5.  Also,
	 * simultaneously shift out and in the 0x00 that is ALWAYS the value
	 * stored in the last byte to be shifted out of the FIFO's DWORD
	 * buffer register.
	 */
	writel(S626_XSD2 | S626_XFIFO_2 | S626_RSD2 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPORT(0));

	/* WAIT FOR THE TRANSACTION TO FINISH ----------------------- */

	/*
	 * Wait for the TSL to finish executing all time slots before
	 * exiting this function.  We must do this so that the next DAC
	 * write doesn't start, thereby enabling clock/chip select signals:
	 *
	 * 1. Before the TSL sequence cycles back to slot 0, which disables
	 *    the clock/cs signal gating and traps slot // list execution.
	 *    we have not yet finished slot 5 then the clock/cs signals are
	 *    still gated and we have not finished transmitting the stream.
	 *
	 * 2. While slots 2-5 are executing due to a late slot 0 trap.  In
	 *    this case, the slot sequence is currently repeating, but with
	 *    clock/cs signals disabled.  We must wait for slot 0 to trap
	 *    execution before setting up the next DAC setpoint DMA transfer
	 *    and enabling the clock/cs signals.  To detect the end of slot 5,
	 *    we test for the FB_BUFFER2 MSB contents to be equal to 0xFF.  If
	 *    the TSL has not yet finished executing slot 5 ...
	 */
	if (readl(dev->mmio + S626_P_FB_BUFFER2) & 0xff000000) {
		/*
		 * The trap was set on time and we are still executing somewhere
		 * in slots 2-5, so we now wait for slot 0 to execute and trap
		 * TSL execution.  This is detected when FB_BUFFER2 MSB changes
		 * from 0xFF to 0x00, which slot 0 causes to happen by shifting
		 * out/in on SD2 the 0x00 that is always referenced by slot 5.
		 */
		ret = comedi_timeout(dev, NULL, NULL, s626_send_dac_eoc,
				     s626_send_dac_wait_fb_buffer2_msb_00);
		if (ret) {
			dev_err(dev->class_dev,
				"TSL timeout waiting for slot 0 to execute\n");
			return ret;
		}
	}
	/*
	 * Either (1) we were too late setting the slot 0 trap; the TSL
	 * sequencer restarted slot 0 before we could set the EOS trap flag,
	 * or (2) we were not late and execution is now trapped at slot 0.
	 * In either case, we must now change slot 0 so that it will store
	 * value 0xFF (instead of 0x00) to FB_BUFFER2 next time it executes.
	 * In order to do this, we reprogram slot 0 so that it will shift in
	 * SD3, which is driven only by a pull-up resistor.
	 */
	writel(S626_RSD3 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPORT(0));

	/*
	 * Wait for slot 0 to execute, at which time the TSL is setup for
	 * the next DAC write.  This is detected when FB_BUFFER2 MSB changes
	 * from 0x00 to 0xFF.
	 */
	ret = comedi_timeout(dev, NULL, NULL, s626_send_dac_eoc,
			     s626_send_dac_wait_fb_buffer2_msb_ff);
	if (ret) {
		dev_err(dev->class_dev,
			"TSL timeout waiting for slot 0 to execute\n");
		return ret;
	}
	return 0;
}