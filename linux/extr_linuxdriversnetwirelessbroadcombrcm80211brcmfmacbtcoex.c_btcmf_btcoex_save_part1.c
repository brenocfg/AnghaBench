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
struct brcmf_if {int dummy; } ;
struct brcmf_btcoex_info {int saved_regs_part1; int /*<<< orphan*/  reg68; int /*<<< orphan*/  reg41; int /*<<< orphan*/  reg66; TYPE_1__* vif; } ;
struct TYPE_2__ {struct brcmf_if* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  brcmf_btcoex_params_read (struct brcmf_if*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btcmf_btcoex_save_part1(struct brcmf_btcoex_info *btci)
{
	struct brcmf_if *ifp = btci->vif->ifp;

	if (!btci->saved_regs_part1) {
		/* Retrieve and save original reg value */
		brcmf_btcoex_params_read(ifp, 66, &btci->reg66);
		brcmf_btcoex_params_read(ifp, 41, &btci->reg41);
		brcmf_btcoex_params_read(ifp, 68, &btci->reg68);
		btci->saved_regs_part1 = true;
		brcmf_dbg(INFO,
			  "saved btc_params regs (66,41,68) 0x%x 0x%x 0x%x\n",
			  btci->reg66, btci->reg41,
			  btci->reg68);
	}
}