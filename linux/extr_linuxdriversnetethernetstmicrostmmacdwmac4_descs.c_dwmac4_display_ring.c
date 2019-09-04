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
struct dma_desc {int /*<<< orphan*/  des3; int /*<<< orphan*/  des2; int /*<<< orphan*/  des1; int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__ virt_to_phys (struct dma_desc*) ; 

__attribute__((used)) static void dwmac4_display_ring(void *head, unsigned int size, bool rx)
{
	struct dma_desc *p = (struct dma_desc *)head;
	int i;

	pr_info("%s descriptor ring:\n", rx ? "RX" : "TX");

	for (i = 0; i < size; i++) {
		pr_info("%03d [0x%x]: 0x%x 0x%x 0x%x 0x%x\n",
			i, (unsigned int)virt_to_phys(p),
			le32_to_cpu(p->des0), le32_to_cpu(p->des1),
			le32_to_cpu(p->des2), le32_to_cpu(p->des3));
		p++;
	}
}