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
typedef  int /*<<< orphan*/  u32 ;
struct pch_udc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_DEVIRQSTS_ADDR ; 
 int /*<<< orphan*/  pch_udc_writel (struct pch_udc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pch_udc_write_device_interrupts(struct pch_udc_dev *dev,
						     u32 val)
{
	pch_udc_writel(dev, val, UDC_DEVIRQSTS_ADDR);
}