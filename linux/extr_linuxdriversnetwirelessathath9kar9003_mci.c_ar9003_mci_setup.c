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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath9k_hw_mci {void* sched_addr; int /*<<< orphan*/  gpm_len; void* gpm_buf; void* gpm_addr; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int ar9003_mci_reset (struct ath_hw*,int,int,int) ; 

int ar9003_mci_setup(struct ath_hw *ah, u32 gpm_addr, void *gpm_buf,
		     u16 len, u32 sched_addr)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->gpm_addr = gpm_addr;
	mci->gpm_buf = gpm_buf;
	mci->gpm_len = len;
	mci->sched_addr = sched_addr;

	return ar9003_mci_reset(ah, true, true, true);
}