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
struct brcmf_core {int dummy; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  pub; int /*<<< orphan*/  ctx; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* activate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_ARM_CM3 ; 
 int /*<<< orphan*/  BCMA_CORE_INTERNAL_MEM ; 
 struct brcmf_core* brcmf_chip_get_core (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_iscoreup (struct brcmf_core*) ; 
 int /*<<< orphan*/  brcmf_chip_resetcore (struct brcmf_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool brcmf_chip_cm3_set_active(struct brcmf_chip_priv *chip)
{
	struct brcmf_core *core;

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_INTERNAL_MEM);
	if (!brcmf_chip_iscoreup(core)) {
		brcmf_err("SOCRAM core is down after reset?\n");
		return false;
	}

	chip->ops->activate(chip->ctx, &chip->pub, 0);

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_ARM_CM3);
	brcmf_chip_resetcore(core, 0, 0, 0);

	return true;
}