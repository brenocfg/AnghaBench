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
struct ni_gpct_device {int variant; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int GI_DMA_ENABLE ; 
 unsigned int GI_DMA_INT_ENA ; 
 unsigned int GI_DMA_WRITE ; 
 unsigned int GI_READ_ACKS_IRQ ; 
 unsigned int GI_WRITE_ACKS_IRQ ; 
 int /*<<< orphan*/  NITIO_DMA_CFG_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_INPUT_SEL_REG (unsigned int) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void ni_tio_configure_dma(struct ni_gpct *counter,
				 bool enable, bool read)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int mask;
	unsigned int bits;

	mask = GI_READ_ACKS_IRQ | GI_WRITE_ACKS_IRQ;
	bits = 0;

	if (enable) {
		if (read)
			bits |= GI_READ_ACKS_IRQ;
		else
			bits |= GI_WRITE_ACKS_IRQ;
	}
	ni_tio_set_bits(counter, NITIO_INPUT_SEL_REG(cidx), mask, bits);

	switch (counter_dev->variant) {
	case ni_gpct_variant_e_series:
		break;
	case ni_gpct_variant_m_series:
	case ni_gpct_variant_660x:
		mask = GI_DMA_ENABLE | GI_DMA_INT_ENA | GI_DMA_WRITE;
		bits = 0;

		if (enable)
			bits |= GI_DMA_ENABLE | GI_DMA_INT_ENA;
		if (!read)
			bits |= GI_DMA_WRITE;
		ni_tio_set_bits(counter, NITIO_DMA_CFG_REG(cidx), mask, bits);
		break;
	}
}