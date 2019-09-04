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
struct ni_private {scalar_t__ is_622x; scalar_t__ is_6143; scalar_t__ is_611x; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 unsigned int NISTC_AI_CMD1_DISARM ; 
 int /*<<< orphan*/  NISTC_AI_CMD1_REG ; 
 int /*<<< orphan*/  NISTC_AI_MODE1_REG ; 
 unsigned int NISTC_AI_MODE1_RSVD ; 
 unsigned int NISTC_AI_MODE1_START_STOP ; 
 int /*<<< orphan*/  NISTC_AI_MODE2_REG ; 
 unsigned int NISTC_AI_MODE3_FIFO_MODE_NE ; 
 int /*<<< orphan*/  NISTC_AI_MODE3_REG ; 
 unsigned int NISTC_AI_OUT_CTRL_CONVERT_HIGH ; 
 unsigned int NISTC_AI_OUT_CTRL_CONVERT_LOW ; 
 unsigned int NISTC_AI_OUT_CTRL_EXTMUX_CLK_SEL (int /*<<< orphan*/ ) ; 
 unsigned int NISTC_AI_OUT_CTRL_LOCALMUX_CLK_SEL (int) ; 
 int /*<<< orphan*/  NISTC_AI_OUT_CTRL_REG ; 
 unsigned int NISTC_AI_OUT_CTRL_SCAN_IN_PROG_SEL (int) ; 
 unsigned int NISTC_AI_OUT_CTRL_SC_TC_SEL (int) ; 
 unsigned int NISTC_AI_PERSONAL_CONVERT_PW ; 
 unsigned int NISTC_AI_PERSONAL_LOCALMUX_CLK_PW ; 
 int /*<<< orphan*/  NISTC_AI_PERSONAL_REG ; 
 unsigned int NISTC_AI_PERSONAL_SHIFTIN_PW ; 
 unsigned int NISTC_AI_PERSONAL_SOC_POLARITY ; 
 unsigned int NISTC_INTA_ACK_AI_ALL ; 
 int /*<<< orphan*/  NISTC_INTA_ACK_REG ; 
 int /*<<< orphan*/  NISTC_INTA_ENA_AI_MASK ; 
 int /*<<< orphan*/  NISTC_INTA_ENA_REG ; 
 unsigned int NISTC_RESET_AI ; 
 unsigned int NISTC_RESET_AI_CFG_END ; 
 unsigned int NISTC_RESET_AI_CFG_START ; 
 int /*<<< orphan*/  NISTC_RESET_REG ; 
 int /*<<< orphan*/  NI_E_MISC_CMD_EXT_ATRIG ; 
 int /*<<< orphan*/  NI_E_MISC_CMD_REG ; 
 int /*<<< orphan*/  ni_clear_ai_fifo (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_release_ai_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writeb (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ai_reset(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct ni_private *devpriv = dev->private;
	unsigned int ai_personal;
	unsigned int ai_out_ctrl;

	ni_release_ai_mite_channel(dev);
	/* ai configuration */
	ni_stc_writew(dev, NISTC_RESET_AI_CFG_START | NISTC_RESET_AI,
		      NISTC_RESET_REG);

	ni_set_bits(dev, NISTC_INTA_ENA_REG, NISTC_INTA_ENA_AI_MASK, 0);

	ni_clear_ai_fifo(dev);

	if (!devpriv->is_6143)
		ni_writeb(dev, NI_E_MISC_CMD_EXT_ATRIG, NI_E_MISC_CMD_REG);

	ni_stc_writew(dev, NISTC_AI_CMD1_DISARM, NISTC_AI_CMD1_REG);
	ni_stc_writew(dev, NISTC_AI_MODE1_START_STOP |
			   NISTC_AI_MODE1_RSVD
			    /*| NISTC_AI_MODE1_TRIGGER_ONCE */,
		      NISTC_AI_MODE1_REG);
	ni_stc_writew(dev, 0, NISTC_AI_MODE2_REG);
	/* generate FIFO interrupts on non-empty */
	ni_stc_writew(dev, NISTC_AI_MODE3_FIFO_MODE_NE,
		      NISTC_AI_MODE3_REG);

	ai_personal = NISTC_AI_PERSONAL_SHIFTIN_PW |
		      NISTC_AI_PERSONAL_SOC_POLARITY |
		      NISTC_AI_PERSONAL_LOCALMUX_CLK_PW;
	ai_out_ctrl = NISTC_AI_OUT_CTRL_SCAN_IN_PROG_SEL(3) |
		      NISTC_AI_OUT_CTRL_EXTMUX_CLK_SEL(0) |
		      NISTC_AI_OUT_CTRL_LOCALMUX_CLK_SEL(2) |
		      NISTC_AI_OUT_CTRL_SC_TC_SEL(3);
	if (devpriv->is_611x) {
		ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_HIGH;
	} else if (devpriv->is_6143) {
		ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_LOW;
	} else {
		ai_personal |= NISTC_AI_PERSONAL_CONVERT_PW;
		if (devpriv->is_622x)
			ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_HIGH;
		else
			ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_LOW;
	}
	ni_stc_writew(dev, ai_personal, NISTC_AI_PERSONAL_REG);
	ni_stc_writew(dev, ai_out_ctrl, NISTC_AI_OUT_CTRL_REG);

	/* the following registers should not be changed, because there
	 * are no backup registers in devpriv.  If you want to change
	 * any of these, add a backup register and other appropriate code:
	 *      NISTC_AI_MODE1_REG
	 *      NISTC_AI_MODE3_REG
	 *      NISTC_AI_PERSONAL_REG
	 *      NISTC_AI_OUT_CTRL_REG
	 */

	/* clear interrupts */
	ni_stc_writew(dev, NISTC_INTA_ACK_AI_ALL, NISTC_INTA_ACK_REG);

	ni_stc_writew(dev, NISTC_RESET_AI_CFG_END, NISTC_RESET_REG);

	return 0;
}