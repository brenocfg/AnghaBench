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
typedef  scalar_t__ u32 ;
struct ath10k_ahb {scalar_t__ gcc_mem; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 scalar_t__ ioread32 (scalar_t__) ; 

__attribute__((used)) static u32 ath10k_ahb_gcc_read32(struct ath10k *ar, u32 offset)
{
	struct ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	return ioread32(ar_ahb->gcc_mem + offset);
}