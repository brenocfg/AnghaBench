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
struct ath10k_pci {struct ath10k_ahb* ahb; } ;
struct ath10k_ahb {int dummy; } ;
struct ath10k {scalar_t__ drv_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ath10k_ahb *ath10k_ahb_priv(struct ath10k *ar)
{
	return &((struct ath10k_pci *)ar->drv_priv)->ahb[0];
}