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
struct dma_info {scalar_t__ ntxd; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int D64_XS0_CD_MASK ; 
 int /*<<< orphan*/  DMA64TXREGOFFS (struct dma_info*,int /*<<< orphan*/ ) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr ; 
 int /*<<< orphan*/  status0 ; 

__attribute__((used)) static bool dma64_txidle(struct dma_info *di)
{
	if (di->ntxd == 0)
		return true;

	return ((bcma_read32(di->core,
			     DMA64TXREGOFFS(di, status0)) & D64_XS0_CD_MASK) ==
		(bcma_read32(di->core, DMA64TXREGOFFS(di, ptr)) &
		 D64_XS0_CD_MASK));
}