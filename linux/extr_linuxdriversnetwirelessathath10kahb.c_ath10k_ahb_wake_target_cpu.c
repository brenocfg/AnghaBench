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
typedef  int u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ATH10K_AHB_CORE_CTRL_CPU_INTR_MASK ; 
 int CORE_CTRL_ADDRESS ; 
 int SOC_CORE_BASE_ADDRESS ; 
 int ath10k_ahb_read32 (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_ahb_write32 (struct ath10k*,int,int) ; 

__attribute__((used)) static int ath10k_ahb_wake_target_cpu(struct ath10k *ar)
{
	u32 addr, val;

	addr = SOC_CORE_BASE_ADDRESS | CORE_CTRL_ADDRESS;
	val = ath10k_ahb_read32(ar, addr);
	val |= ATH10K_AHB_CORE_CTRL_CPU_INTR_MASK;
	ath10k_ahb_write32(ar, addr, val);

	return 0;
}