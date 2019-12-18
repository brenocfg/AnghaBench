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
struct aaci_runtime {int cr; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AACI_IE ; 
 scalar_t__ AACI_RXCR ; 
 int CR_EN ; 
 int IE_ORIE ; 
 int IE_RXIE ; 
 int /*<<< orphan*/  SR_RXB ; 
 int /*<<< orphan*/  aaci_chan_wait_ready (struct aaci_runtime*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void aaci_pcm_capture_stop(struct aaci_runtime *aacirun)
{
	u32 ie;

	aaci_chan_wait_ready(aacirun, SR_RXB);

	ie = readl(aacirun->base + AACI_IE);
	ie &= ~(IE_ORIE | IE_RXIE);
	writel(ie, aacirun->base+AACI_IE);

	aacirun->cr &= ~CR_EN;

	writel(aacirun->cr, aacirun->base + AACI_RXCR);
}