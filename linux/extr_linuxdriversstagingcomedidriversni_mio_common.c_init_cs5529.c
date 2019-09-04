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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CS5529_CFG_CALIB_BOTH_SELF ; 
 unsigned int CS5529_CFG_PORT_FLAG ; 
 int /*<<< orphan*/  CS5529_CFG_REG ; 
 unsigned int CS5529_CFG_WORD_RATE_2180 ; 
 int /*<<< orphan*/  cs5529_config_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5529_do_conversion (struct comedi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_cs5529(struct comedi_device *dev)
{
	unsigned int config_bits = CS5529_CFG_PORT_FLAG |
				   CS5529_CFG_WORD_RATE_2180;

#if 1
	/* do self-calibration */
	cs5529_config_write(dev, config_bits | CS5529_CFG_CALIB_BOTH_SELF,
			    CS5529_CFG_REG);
	/* need to force a conversion for calibration to run */
	cs5529_do_conversion(dev, NULL);
#else
	/* force gain calibration to 1 */
	cs5529_config_write(dev, 0x400000, CS5529_GAIN_REG);
	cs5529_config_write(dev, config_bits | CS5529_CFG_CALIB_OFFSET_SELF,
			    CS5529_CFG_REG);
	if (cs5529_wait_for_idle(dev))
		dev_err(dev->class_dev,
			"timeout or signal in %s\n", __func__);
#endif
	return 0;
}