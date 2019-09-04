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
struct img_spfi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int SPFI_INTERRUPT_ALLDONETRIG ; 
 int /*<<< orphan*/  SPFI_INTERRUPT_CLEAR ; 
 int /*<<< orphan*/  SPFI_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int spfi_readl (struct img_spfi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spfi_reset (struct img_spfi*) ; 
 int /*<<< orphan*/  spfi_writel (struct img_spfi*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int spfi_wait_all_done(struct img_spfi *spfi)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(50);

	while (time_before(jiffies, timeout)) {
		u32 status = spfi_readl(spfi, SPFI_INTERRUPT_STATUS);

		if (status & SPFI_INTERRUPT_ALLDONETRIG) {
			spfi_writel(spfi, SPFI_INTERRUPT_ALLDONETRIG,
				    SPFI_INTERRUPT_CLEAR);
			return 0;
		}
		cpu_relax();
	}

	dev_err(spfi->dev, "Timed out waiting for transaction to complete\n");
	spfi_reset(spfi);

	return -ETIMEDOUT;
}