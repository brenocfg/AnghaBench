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

/* Variables and functions */
 int /*<<< orphan*/  DMA_CONTROL_EFC ; 
 int /*<<< orphan*/  DMA_CONTROL_RFA_MASK ; 
 int /*<<< orphan*/  DMA_CONTROL_RFD_MASK ; 
 int /*<<< orphan*/  RFA_FULL_MINUS_1K ; 
 int /*<<< orphan*/  RFD_FULL_MINUS_2K ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static u32 dwmac1000_configure_fc(u32 csr6, int rxfifosz)
{
	csr6 &= ~DMA_CONTROL_RFA_MASK;
	csr6 &= ~DMA_CONTROL_RFD_MASK;

	/* Leave flow control disabled if receive fifo size is less than
	 * 4K or 0. Otherwise, send XOFF when fifo is 1K less than full,
	 * and send XON when 2K less than full.
	 */
	if (rxfifosz < 4096) {
		csr6 &= ~DMA_CONTROL_EFC;
		pr_debug("GMAC: disabling flow control, rxfifo too small(%d)\n",
			 rxfifosz);
	} else {
		csr6 |= DMA_CONTROL_EFC;
		csr6 |= RFA_FULL_MINUS_1K;
		csr6 |= RFD_FULL_MINUS_2K;
	}
	return csr6;
}