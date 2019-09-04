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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct brcmf_core_priv {TYPE_1__ pub; struct brcmf_chip_priv* chip; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  ctx; TYPE_2__* ops; } ;
struct TYPE_4__ {int (* read32 ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int CORE_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSB_IMSTATE_REJECT ; 
 int SSB_TMSLOW_CLOCK ; 
 int SSB_TMSLOW_REJECT ; 
 int SSB_TMSLOW_RESET ; 
 int /*<<< orphan*/  sbtmstatelow ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool brcmf_chip_sb_iscoreup(struct brcmf_core_priv *core)
{
	struct brcmf_chip_priv *ci;
	u32 regdata;
	u32 address;

	ci = core->chip;
	address = CORE_SB(core->pub.base, sbtmstatelow);
	regdata = ci->ops->read32(ci->ctx, address);
	regdata &= (SSB_TMSLOW_RESET | SSB_TMSLOW_REJECT |
		    SSB_IMSTATE_REJECT | SSB_TMSLOW_CLOCK);
	return SSB_TMSLOW_CLOCK == regdata;
}