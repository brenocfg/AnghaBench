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
struct spi_master {int dummy; } ;
struct omap2_mcspi {scalar_t__ base; } ;

/* Variables and functions */
 struct omap2_mcspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void mcspi_write_reg(struct spi_master *master,
		int idx, u32 val)
{
	struct omap2_mcspi *mcspi = spi_master_get_devdata(master);

	writel_relaxed(val, mcspi->base + idx);
}