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
struct ni_private {int /*<<< orphan*/  rtsi_trig_b_output_reg; int /*<<< orphan*/  is_m_series; int /*<<< orphan*/  rtsi_trig_a_output_reg; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
 unsigned int NISTC_RTSI_TRIG_NUM_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int NISTC_RTSI_TRIG_OLD_CLK_CHAN ; 
 unsigned int NISTC_RTSI_TRIG_TO_SRC (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int NI_RTSI_OUTPUT_RTSI_OSC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static unsigned int ni_get_rtsi_routing(struct comedi_device *dev,
					unsigned int chan)
{
	struct ni_private *devpriv = dev->private;

	if (chan < 4) {
		return NISTC_RTSI_TRIG_TO_SRC(chan,
					      devpriv->rtsi_trig_a_output_reg);
	} else if (chan < NISTC_RTSI_TRIG_NUM_CHAN(devpriv->is_m_series)) {
		return NISTC_RTSI_TRIG_TO_SRC(chan,
					      devpriv->rtsi_trig_b_output_reg);
	} else {
		if (chan == NISTC_RTSI_TRIG_OLD_CLK_CHAN)
			return NI_RTSI_OUTPUT_RTSI_OSC;
		dev_err(dev->class_dev, "bug! should never get here?\n");
		return 0;
	}
}