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
struct pch_udc_dev {int dummy; } ;

/* Variables and functions */
 unsigned long PCH_UDC_CSR (unsigned int) ; 
 int /*<<< orphan*/  pch_udc_csr_busy (struct pch_udc_dev*) ; 
 int /*<<< orphan*/  pch_udc_writel (struct pch_udc_dev*,unsigned long,unsigned long) ; 

__attribute__((used)) static void pch_udc_write_csr(struct pch_udc_dev *dev, unsigned long val,
			       unsigned int ep)
{
	unsigned long reg = PCH_UDC_CSR(ep);

	pch_udc_csr_busy(dev);		/* Wait till idle */
	pch_udc_writel(dev, val, reg);
	pch_udc_csr_busy(dev);		/* Wait till idle */
}