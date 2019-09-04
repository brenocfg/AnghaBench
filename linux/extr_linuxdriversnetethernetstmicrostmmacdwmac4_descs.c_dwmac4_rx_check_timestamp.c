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
typedef  unsigned int u32 ;
struct dma_desc {int /*<<< orphan*/  des3; int /*<<< orphan*/  des1; int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RDES3_CONTEXT_DESCRIPTOR ; 
 unsigned int RDES3_CONTEXT_DESCRIPTOR_SHIFT ; 
 unsigned int RDES3_OWN ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int dwmac4_rx_check_timestamp(void *desc)
{
	struct dma_desc *p = (struct dma_desc *)desc;
	unsigned int rdes0 = le32_to_cpu(p->des0);
	unsigned int rdes1 = le32_to_cpu(p->des1);
	unsigned int rdes3 = le32_to_cpu(p->des3);
	u32 own, ctxt;
	int ret = 1;

	own = rdes3 & RDES3_OWN;
	ctxt = ((rdes3 & RDES3_CONTEXT_DESCRIPTOR)
		>> RDES3_CONTEXT_DESCRIPTOR_SHIFT);

	if (likely(!own && ctxt)) {
		if ((rdes0 == 0xffffffff) && (rdes1 == 0xffffffff))
			/* Corrupted value */
			ret = -EINVAL;
		else
			/* A valid Timestamp is ready to be read */
			ret = 0;
	}

	/* Timestamp not ready */
	return ret;
}