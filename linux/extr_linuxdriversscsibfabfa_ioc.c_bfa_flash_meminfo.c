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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DMA_ALIGN_SZ ; 
 int /*<<< orphan*/  BFA_FLASH_DMA_BUF_SZ ; 
 int /*<<< orphan*/  BFA_ROUNDUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32
bfa_flash_meminfo(bfa_boolean_t mincfg)
{
	/* min driver doesn't need flash */
	if (mincfg)
		return 0;
	return BFA_ROUNDUP(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
}