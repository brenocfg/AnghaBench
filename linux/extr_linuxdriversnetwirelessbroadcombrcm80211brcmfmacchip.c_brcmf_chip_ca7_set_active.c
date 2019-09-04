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
struct brcmf_core {int dummy; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  pub; int /*<<< orphan*/  ctx; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* activate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARMCR4_BCMA_IOCTL_CPUHALT ; 
 int /*<<< orphan*/  BCMA_CORE_ARM_CA7 ; 
 struct brcmf_core* brcmf_chip_get_core (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_resetcore (struct brcmf_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool brcmf_chip_ca7_set_active(struct brcmf_chip_priv *chip, u32 rstvec)
{
	struct brcmf_core *core;

	chip->ops->activate(chip->ctx, &chip->pub, rstvec);

	/* restore ARM */
	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_ARM_CA7);
	brcmf_chip_resetcore(core, ARMCR4_BCMA_IOCTL_CPUHALT, 0, 0);

	return true;
}