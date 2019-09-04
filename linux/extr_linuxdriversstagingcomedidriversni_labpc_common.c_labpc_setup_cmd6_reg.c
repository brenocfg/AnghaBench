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
struct labpc_private {int /*<<< orphan*/  cmd6; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct labpc_boardinfo {int /*<<< orphan*/  is_labpc1200; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct labpc_private* private; struct labpc_boardinfo* board_ptr; } ;
typedef  enum transfer_type { ____Placeholder_transfer_type } transfer_type ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 unsigned int AREF_GROUND ; 
 int /*<<< orphan*/  CMD6_ADCUNI ; 
 int /*<<< orphan*/  CMD6_DQINTEN ; 
 int /*<<< orphan*/  CMD6_HFINTEN ; 
 int /*<<< orphan*/  CMD6_NRSE ; 
 int /*<<< orphan*/  CMD6_REG ; 
 int /*<<< orphan*/  CMD6_SCANUP ; 
 int MODE_MULT_CHAN_UP ; 
 scalar_t__ comedi_range_is_unipolar (struct comedi_subdevice*,unsigned int) ; 
 int fifo_half_full_transfer ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void labpc_setup_cmd6_reg(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 enum scan_mode mode,
				 enum transfer_type xfer,
				 unsigned int range,
				 unsigned int aref,
				 bool ena_intr)
{
	const struct labpc_boardinfo *board = dev->board_ptr;
	struct labpc_private *devpriv = dev->private;

	if (!board->is_labpc1200)
		return;

	/* reference inputs to ground or common? */
	if (aref != AREF_GROUND)
		devpriv->cmd6 |= CMD6_NRSE;
	else
		devpriv->cmd6 &= ~CMD6_NRSE;

	/* bipolar or unipolar range? */
	if (comedi_range_is_unipolar(s, range))
		devpriv->cmd6 |= CMD6_ADCUNI;
	else
		devpriv->cmd6 &= ~CMD6_ADCUNI;

	/*  interrupt on fifo half full? */
	if (xfer == fifo_half_full_transfer)
		devpriv->cmd6 |= CMD6_HFINTEN;
	else
		devpriv->cmd6 &= ~CMD6_HFINTEN;

	/* enable interrupt on counter a1 terminal count? */
	if (ena_intr)
		devpriv->cmd6 |= CMD6_DQINTEN;
	else
		devpriv->cmd6 &= ~CMD6_DQINTEN;

	/* are we scanning up or down through channels? */
	if (mode == MODE_MULT_CHAN_UP)
		devpriv->cmd6 |= CMD6_SCANUP;
	else
		devpriv->cmd6 &= ~CMD6_SCANUP;

	devpriv->write_byte(dev, devpriv->cmd6, CMD6_REG);
}