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
typedef  int u32 ;
struct RxDesc {int /*<<< orphan*/  opts1; } ;

/* Variables and functions */
 int DescOwn ; 
 int R8169_RX_BUF_SIZE ; 
 int RingEnd ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rtl8169_mark_to_asic(struct RxDesc *desc)
{
	u32 eor = le32_to_cpu(desc->opts1) & RingEnd;

	/* Force memory writes to complete before releasing descriptor */
	dma_wmb();

	desc->opts1 = cpu_to_le32(DescOwn | eor | R8169_RX_BUF_SIZE);
}