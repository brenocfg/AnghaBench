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
struct TYPE_4__ {TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  ACMR1; int /*<<< orphan*/  ACMR0; int /*<<< orphan*/  ACSR1; int /*<<< orphan*/  ACSR0; int /*<<< orphan*/  MIEN; int /*<<< orphan*/  MLBC0; } ;

/* Variables and functions */
 int MLBC0_MLBEN_BIT ; 
 int /*<<< orphan*/  dim2_clear_ctram () ; 
 int /*<<< orphan*/  dimcb_io_write (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ g ; 

__attribute__((used)) static void dim2_cleanup(void)
{
	/* disable MediaLB */
	dimcb_io_write(&g.dim2->MLBC0, false << MLBC0_MLBEN_BIT);

	dim2_clear_ctram();

	/* disable mlb_int interrupt */
	dimcb_io_write(&g.dim2->MIEN, 0);

	/* clear status for all dma channels */
	dimcb_io_write(&g.dim2->ACSR0, 0xFFFFFFFF);
	dimcb_io_write(&g.dim2->ACSR1, 0xFFFFFFFF);

	/* mask interrupts for all channels */
	dimcb_io_write(&g.dim2->ACMR0, 0);
	dimcb_io_write(&g.dim2->ACMR1, 0);
}