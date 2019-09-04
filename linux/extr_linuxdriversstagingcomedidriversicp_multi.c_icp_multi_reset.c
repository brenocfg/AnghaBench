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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ ICP_MULTI_AO ; 
 scalar_t__ ICP_MULTI_DAC_CSR ; 
 unsigned int ICP_MULTI_DAC_CSR_CHAN (int) ; 
 unsigned int ICP_MULTI_DAC_CSR_ST ; 
 scalar_t__ ICP_MULTI_DO ; 
 scalar_t__ ICP_MULTI_INT_EN ; 
 unsigned int ICP_MULTI_INT_MASK ; 
 scalar_t__ ICP_MULTI_INT_STAT ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int icp_multi_reset(struct comedi_device *dev)
{
	int i;

	/* Disable all interrupts and clear any requests */
	writew(0, dev->mmio + ICP_MULTI_INT_EN);
	writew(ICP_MULTI_INT_MASK, dev->mmio + ICP_MULTI_INT_STAT);

	/* Reset the analog output channels to 0V */
	for (i = 0; i < 4; i++) {
		unsigned int dac_csr = ICP_MULTI_DAC_CSR_CHAN(i);

		/* Select channel and 0..5V range */
		writew(dac_csr, dev->mmio + ICP_MULTI_DAC_CSR);

		/* Output 0V */
		writew(0, dev->mmio + ICP_MULTI_AO);

		/* Set start conversion bit to write data to channel */
		writew(dac_csr | ICP_MULTI_DAC_CSR_ST,
		       dev->mmio + ICP_MULTI_DAC_CSR);
		udelay(1);
	}

	/* Digital outputs to 0 */
	writew(0, dev->mmio + ICP_MULTI_DO);

	return 0;
}