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
typedef  int /*<<< orphan*/  uint ;
typedef  int u32 ;
struct dma_info {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int D64_XC_AE ; 
 int /*<<< orphan*/  bcma_mask32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool _dma64_addrext(struct dma_info *di, uint ctrl_offset)
{
	u32 w;
	bcma_set32(di->core, ctrl_offset, D64_XC_AE);
	w = bcma_read32(di->core, ctrl_offset);
	bcma_mask32(di->core, ctrl_offset, ~D64_XC_AE);
	return (w & D64_XC_AE) == D64_XC_AE;
}