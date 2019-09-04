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
struct fsl_lpspi_data {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ IMX7ULP_FSR ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int fsl_lpspi_txfifo_empty(struct fsl_lpspi_data *fsl_lpspi)
{
	u32 txcnt;
	unsigned long orig_jiffies = jiffies;

	do {
		txcnt = readl(fsl_lpspi->base + IMX7ULP_FSR) & 0xff;

		if (time_after(jiffies, orig_jiffies + msecs_to_jiffies(500))) {
			dev_dbg(fsl_lpspi->dev, "txfifo empty timeout\n");
			return -ETIMEDOUT;
		}
		cond_resched();

	} while (txcnt);

	return 0;
}