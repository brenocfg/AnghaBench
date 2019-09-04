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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  des0; } ;
struct dma_extended_desc {TYPE_1__ basic; } ;
struct dma_desc {int /*<<< orphan*/  des3; int /*<<< orphan*/  des2; } ;

/* Variables and functions */
 int RDES0_IPC_CSUM_ERROR ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enh_desc_get_rx_timestamp_status(void *desc, void *next_desc,
					    u32 ats)
{
	if (ats) {
		struct dma_extended_desc *p = (struct dma_extended_desc *)desc;
		return (le32_to_cpu(p->basic.des0) & RDES0_IPC_CSUM_ERROR) >> 7;
	} else {
		struct dma_desc *p = (struct dma_desc *)desc;
		if ((le32_to_cpu(p->des2) == 0xffffffff) &&
		    (le32_to_cpu(p->des3) == 0xffffffff))
			/* timestamp is corrupted, hence don't store it */
			return 0;
		else
			return 1;
	}
}