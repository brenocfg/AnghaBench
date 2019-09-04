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
struct pch_udc_dev {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static inline u32 pch_udc_readl(struct pch_udc_dev *dev, unsigned long reg)
{
	return ioread32(dev->base_addr + reg);
}