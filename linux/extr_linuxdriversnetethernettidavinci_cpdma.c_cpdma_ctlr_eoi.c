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
struct cpdma_ctlr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPDMA_MACEOIVECTOR ; 
 int /*<<< orphan*/  dma_reg_write (struct cpdma_ctlr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cpdma_ctlr_eoi(struct cpdma_ctlr *ctlr, u32 value)
{
	dma_reg_write(ctlr, CPDMA_MACEOIVECTOR, value);
}