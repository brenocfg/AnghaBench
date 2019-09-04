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
 int EPIPE ; 
 unsigned short NISTC_AO_STATUS1_FIFO_HF ; 
 int /*<<< orphan*/  NISTC_AO_STATUS1_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned short ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ni_ao_wait_for_dma_load(struct comedi_device *dev)
{
	static const int timeout = 10000;
	int i;

	for (i = 0; i < timeout; i++) {
		unsigned short b_status;

		b_status = ni_stc_readw(dev, NISTC_AO_STATUS1_REG);
		if (b_status & NISTC_AO_STATUS1_FIFO_HF)
			break;
		/*
		 * If we poll too often, the pci bus activity seems
		 * to slow the dma transfer down.
		 */
		usleep_range(10, 100);
	}
	if (i == timeout) {
		dev_err(dev->class_dev, "timed out waiting for dma load\n");
		return -EPIPE;
	}
	return 0;
}