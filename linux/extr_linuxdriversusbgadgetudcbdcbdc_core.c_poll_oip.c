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
struct bdc {int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDC_BDCSC ; 
 scalar_t__ BDC_CSTS (int /*<<< orphan*/ ) ; 
 scalar_t__ BDC_OIP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  bdc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int poll_oip(struct bdc *bdc, int usec)
{
	u32 status;
	/* Poll till STS!= OIP */
	while (usec) {
		status = bdc_readl(bdc->regs, BDC_BDCSC);
		if (BDC_CSTS(status) != BDC_OIP) {
			dev_dbg(bdc->dev,
				"poll_oip complete status=%d",
				BDC_CSTS(status));
			return 0;
		}
		udelay(10);
		usec -= 10;
	}
	dev_err(bdc->dev, "Err: operation timedout BDCSC: 0x%08x\n", status);

	return -ETIMEDOUT;
}