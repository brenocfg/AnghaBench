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
struct ni_private {int ai_calib_source; scalar_t__ ai_calib_source_enabled; } ;
struct ni_board_struct {int ai_fifo_depth; } ;
struct comedi_device {struct ni_private* private; struct ni_board_struct* board_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI6143_AI_FIFO_FLAG_REG ; 
 int /*<<< orphan*/  NI6143_CALIB_CHAN_REG ; 
 int NI6143_CALIB_CHAN_RELAY_OFF ; 
 int /*<<< orphan*/  NI6143_EOC_SET_REG ; 
 int /*<<< orphan*/  NI6143_MAGIC_REG ; 
 int /*<<< orphan*/  NI6143_PIPELINE_DELAY_REG ; 
 int /*<<< orphan*/  NISTC_INT_CTRL_REG ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writeb (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_6143(struct comedi_device *dev)
{
	const struct ni_board_struct *board = dev->board_ptr;
	struct ni_private *devpriv = dev->private;

	/*  Disable interrupts */
	ni_stc_writew(dev, 0, NISTC_INT_CTRL_REG);

	/*  Initialise 6143 AI specific bits */

	/* Set G0,G1 DMA mode to E series version */
	ni_writeb(dev, 0x00, NI6143_MAGIC_REG);
	/* Set EOCMode, ADCMode and pipelinedelay */
	ni_writeb(dev, 0x80, NI6143_PIPELINE_DELAY_REG);
	/* Set EOC Delay */
	ni_writeb(dev, 0x00, NI6143_EOC_SET_REG);

	/* Set the FIFO half full level */
	ni_writel(dev, board->ai_fifo_depth / 2, NI6143_AI_FIFO_FLAG_REG);

	/*  Strobe Relay disable bit */
	devpriv->ai_calib_source_enabled = 0;
	ni_writew(dev, devpriv->ai_calib_source | NI6143_CALIB_CHAN_RELAY_OFF,
		  NI6143_CALIB_CHAN_REG);
	ni_writew(dev, devpriv->ai_calib_source, NI6143_CALIB_CHAN_REG);
}