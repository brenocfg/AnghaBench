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
struct brcmf_core {int dummy; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_80211 ; 
 int /*<<< orphan*/  BCMA_CORE_ARM_CA7 ; 
 int D11_BCMA_IOCTL_PHYCLOCKEN ; 
 int D11_BCMA_IOCTL_PHYRESET ; 
 int /*<<< orphan*/  brcmf_chip_disable_arm (struct brcmf_chip_priv*,int /*<<< orphan*/ ) ; 
 struct brcmf_core* brcmf_chip_get_core (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_resetcore (struct brcmf_core*,int,int,int) ; 

__attribute__((used)) static inline void
brcmf_chip_ca7_set_passive(struct brcmf_chip_priv *chip)
{
	struct brcmf_core *core;

	brcmf_chip_disable_arm(chip, BCMA_CORE_ARM_CA7);

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_80211);
	brcmf_chip_resetcore(core, D11_BCMA_IOCTL_PHYRESET |
				   D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN,
			     D11_BCMA_IOCTL_PHYCLOCKEN);
}