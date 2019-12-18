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
typedef  int u32 ;
struct omap_dmic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DMIC_CTRL_REG ; 
 int /*<<< orphan*/  OMAP_DMIC_DMAENABLE_CLR_REG ; 
 int OMAP_DMIC_DMA_ENABLE ; 
 int OMAP_DMIC_UP_ENABLE_MASK ; 
 int omap_dmic_read (struct omap_dmic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dmic_write (struct omap_dmic*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void omap_dmic_stop(struct omap_dmic *dmic)
{
	u32 ctrl = omap_dmic_read(dmic, OMAP_DMIC_CTRL_REG);
	omap_dmic_write(dmic, OMAP_DMIC_CTRL_REG,
			ctrl & ~OMAP_DMIC_UP_ENABLE_MASK);

	/* Disable DMA request generation */
	omap_dmic_write(dmic, OMAP_DMIC_DMAENABLE_CLR_REG,
			OMAP_DMIC_DMA_ENABLE);

}