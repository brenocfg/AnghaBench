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
struct aaci_runtime {scalar_t__ base; scalar_t__ fifo; } ;
struct aaci {int maincr; scalar_t__ base; struct aaci_runtime playback; } ;

/* Variables and functions */
 scalar_t__ AACI_MAINCR ; 
 scalar_t__ AACI_SR ; 
 scalar_t__ AACI_TXCR ; 
 int CR_EN ; 
 int CR_FEN ; 
 int CR_SZ16 ; 
 int MAINCR_IE ; 
 int SR_TXFF ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static unsigned int aaci_size_fifo(struct aaci *aaci)
{
	struct aaci_runtime *aacirun = &aaci->playback;
	int i;

	/*
	 * Enable the channel, but don't assign it to any slots, so
	 * it won't empty onto the AC'97 link.
	 */
	writel(CR_FEN | CR_SZ16 | CR_EN, aacirun->base + AACI_TXCR);

	for (i = 0; !(readl(aacirun->base + AACI_SR) & SR_TXFF) && i < 4096; i++)
		writel(0, aacirun->fifo);

	writel(0, aacirun->base + AACI_TXCR);

	/*
	 * Re-initialise the AACI after the FIFO depth test, to
	 * ensure that the FIFOs are empty.  Unfortunately, merely
	 * disabling the channel doesn't clear the FIFO.
	 */
	writel(aaci->maincr & ~MAINCR_IE, aaci->base + AACI_MAINCR);
	readl(aaci->base + AACI_MAINCR);
	udelay(1);
	writel(aaci->maincr, aaci->base + AACI_MAINCR);

	/*
	 * If we hit 4096 entries, we failed.  Go back to the specified
	 * fifo depth.
	 */
	if (i == 4096)
		i = 8;

	return i;
}