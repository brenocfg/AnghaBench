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
struct comedi_device {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NISTC_ADC_FIFO_CLR_REG ; 
 int NISTC_AI_CMD1_CONVERT_PULSE ; 
 int /*<<< orphan*/  NISTC_AI_CMD1_REG ; 
 int NISTC_AI_STATUS1_FIFO_E ; 
 int /*<<< orphan*/  NISTC_AI_STATUS1_REG ; 
 int NI_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ni_prime_channelgain_list(struct comedi_device *dev)
{
	int i;

	ni_stc_writew(dev, NISTC_AI_CMD1_CONVERT_PULSE, NISTC_AI_CMD1_REG);
	for (i = 0; i < NI_TIMEOUT; ++i) {
		if (!(ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
		      NISTC_AI_STATUS1_FIFO_E)) {
			ni_stc_writew(dev, 1, NISTC_ADC_FIFO_CLR_REG);
			return;
		}
		udelay(1);
	}
	dev_err(dev->class_dev, "timeout loading channel/gain list\n");
}