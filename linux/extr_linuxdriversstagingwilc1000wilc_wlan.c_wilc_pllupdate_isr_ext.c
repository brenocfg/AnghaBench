#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct wilc {scalar_t__ io_type; TYPE_1__* hif_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hif_clear_int_ext ) (struct wilc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ HIF_SDIO ; 
 int /*<<< orphan*/  PLL_INT_CLR ; 
 int WILC_PLL_TO_SDIO ; 
 int WILC_PLL_TO_SPI ; 
 scalar_t__ is_wilc1000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_get_chipid (struct wilc*,int) ; 

__attribute__((used)) static void wilc_pllupdate_isr_ext(struct wilc *wilc, u32 int_stats)
{
	int trials = 10;

	wilc->hif_func->hif_clear_int_ext(wilc, PLL_INT_CLR);

	if (wilc->io_type == HIF_SDIO)
		mdelay(WILC_PLL_TO_SDIO);
	else
		mdelay(WILC_PLL_TO_SPI);

	while (!(is_wilc1000(wilc_get_chipid(wilc, true)) && --trials))
		mdelay(1);
}