#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int fcnt; TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  ACTL; int /*<<< orphan*/  HCTL; int /*<<< orphan*/  HCMR1; int /*<<< orphan*/  HCMR0; int /*<<< orphan*/  MLBC0; } ;

/* Variables and functions */
 int ACTL_DMA_MODE_BIT ; 
 int ACTL_DMA_MODE_VAL_DMA_MODE_1 ; 
 int ACTL_SCE_BIT ; 
 int /*<<< orphan*/  HCTL_EN_BIT ; 
 int MLBC0_FCNT_SHIFT ; 
 int MLBC0_MLBCLK_SHIFT ; 
 int MLBC0_MLBEN_BIT ; 
 int MLBC0_MLBPEN_BIT ; 
 int bit_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dim2_cleanup () ; 
 int /*<<< orphan*/  dimcb_io_write (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ g ; 

__attribute__((used)) static void dim2_initialize(bool enable_6pin, u8 mlb_clock)
{
	dim2_cleanup();

	/* configure and enable MediaLB */
	dimcb_io_write(&g.dim2->MLBC0,
		       enable_6pin << MLBC0_MLBPEN_BIT |
		       mlb_clock << MLBC0_MLBCLK_SHIFT |
		       g.fcnt << MLBC0_FCNT_SHIFT |
		       true << MLBC0_MLBEN_BIT);

	/* activate all HBI channels */
	dimcb_io_write(&g.dim2->HCMR0, 0xFFFFFFFF);
	dimcb_io_write(&g.dim2->HCMR1, 0xFFFFFFFF);

	/* enable HBI */
	dimcb_io_write(&g.dim2->HCTL, bit_mask(HCTL_EN_BIT));

	/* configure DMA */
	dimcb_io_write(&g.dim2->ACTL,
		       ACTL_DMA_MODE_VAL_DMA_MODE_1 << ACTL_DMA_MODE_BIT |
		       true << ACTL_SCE_BIT);
}