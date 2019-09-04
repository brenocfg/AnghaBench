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
typedef  int u32 ;
struct brcmf_core_priv {scalar_t__ wrapbase; struct brcmf_chip_priv* chip; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  ctx; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* read32 ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* write32 ) (int /*<<< orphan*/ ,scalar_t__,int) ;} ;

/* Variables and functions */
 scalar_t__ BCMA_IOCTL ; 
 int BCMA_IOCTL_CLK ; 
 int BCMA_IOCTL_FGC ; 
 scalar_t__ BCMA_RESET_CTL ; 
 int BCMA_RESET_CTL_RESET ; 
 int /*<<< orphan*/  SPINWAIT (int,int) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int stub3 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int stub5 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int stub7 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void brcmf_chip_ai_coredisable(struct brcmf_core_priv *core,
				      u32 prereset, u32 reset)
{
	struct brcmf_chip_priv *ci;
	u32 regdata;

	ci = core->chip;

	/* if core is already in reset, skip reset */
	regdata = ci->ops->read32(ci->ctx, core->wrapbase + BCMA_RESET_CTL);
	if ((regdata & BCMA_RESET_CTL_RESET) != 0)
		goto in_reset_configure;

	/* configure reset */
	ci->ops->write32(ci->ctx, core->wrapbase + BCMA_IOCTL,
			 prereset | BCMA_IOCTL_FGC | BCMA_IOCTL_CLK);
	ci->ops->read32(ci->ctx, core->wrapbase + BCMA_IOCTL);

	/* put in reset */
	ci->ops->write32(ci->ctx, core->wrapbase + BCMA_RESET_CTL,
			 BCMA_RESET_CTL_RESET);
	usleep_range(10, 20);

	/* wait till reset is 1 */
	SPINWAIT(ci->ops->read32(ci->ctx, core->wrapbase + BCMA_RESET_CTL) !=
		 BCMA_RESET_CTL_RESET, 300);

in_reset_configure:
	/* in-reset configure */
	ci->ops->write32(ci->ctx, core->wrapbase + BCMA_IOCTL,
			 reset | BCMA_IOCTL_FGC | BCMA_IOCTL_CLK);
	ci->ops->read32(ci->ctx, core->wrapbase + BCMA_IOCTL);
}