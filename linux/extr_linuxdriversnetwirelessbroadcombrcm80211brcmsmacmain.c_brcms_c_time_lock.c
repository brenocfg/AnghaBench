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
struct brcms_c_info {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCTL_TBTTHOLD ; 
 int /*<<< orphan*/  bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 

__attribute__((used)) static void brcms_c_time_lock(struct brcms_c_info *wlc)
{
	bcma_set32(wlc->hw->d11core, D11REGOFFS(maccontrol), MCTL_TBTTHOLD);
	/* Commit the write */
	bcma_read32(wlc->hw->d11core, D11REGOFFS(maccontrol));
}