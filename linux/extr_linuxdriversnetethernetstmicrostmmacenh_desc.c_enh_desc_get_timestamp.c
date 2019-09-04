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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u32 ;
struct dma_extended_desc {int /*<<< orphan*/  des7; int /*<<< orphan*/  des6; } ;
struct dma_desc {int /*<<< orphan*/  des3; int /*<<< orphan*/  des2; } ;

/* Variables and functions */
 unsigned long long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enh_desc_get_timestamp(void *desc, u32 ats, u64 *ts)
{
	u64 ns;

	if (ats) {
		struct dma_extended_desc *p = (struct dma_extended_desc *)desc;
		ns = le32_to_cpu(p->des6);
		/* convert high/sec time stamp value to nanosecond */
		ns += le32_to_cpu(p->des7) * 1000000000ULL;
	} else {
		struct dma_desc *p = (struct dma_desc *)desc;
		ns = le32_to_cpu(p->des2);
		ns += le32_to_cpu(p->des3) * 1000000000ULL;
	}

	*ts = ns;
}