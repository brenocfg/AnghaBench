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
struct MessageUnit_D {int /*<<< orphan*/  outbound_doorbell; } ;
struct AdapterControlBlock {struct MessageUnit_D* pmuD; } ;

/* Variables and functions */
 int ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool arcmsr_hbaD_wait_msgint_ready(struct AdapterControlBlock *pACB)
{
	struct MessageUnit_D *reg = pACB->pmuD;
	int i;

	for (i = 0; i < 2000; i++) {
		if (readl(reg->outbound_doorbell)
			& ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE) {
			writel(ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE,
				reg->outbound_doorbell);
			return true;
		}
		msleep(10);
	} /* max 20 seconds */
	return false;
}