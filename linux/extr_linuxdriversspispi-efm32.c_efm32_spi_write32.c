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
struct efm32_spi_ddata {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void efm32_spi_write32(struct efm32_spi_ddata *ddata,
		u32 value, unsigned offset)
{
	writel_relaxed(value, ddata->base + offset);
}