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
struct brcmf_core {int /*<<< orphan*/  rev; int /*<<< orphan*/  base; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  ctx; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read32 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBCOREREV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbidhigh ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_chip_sb_corerev(struct brcmf_chip_priv *ci,
				  struct brcmf_core *core)
{
	u32 regdata;

	regdata = ci->ops->read32(ci->ctx, CORE_SB(core->base, sbidhigh));
	core->rev = SBCOREREV(regdata);
}