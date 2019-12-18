#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct azx {TYPE_2__* card; } ;
struct TYPE_4__ {int* res; } ;
struct TYPE_6__ {TYPE_1__ rirb; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_IRS_VALID ; 
 int EIO ; 
 int /*<<< orphan*/  IR ; 
 int /*<<< orphan*/  IRS ; 
 TYPE_3__* azx_bus (struct azx*) ; 
 int azx_readl (struct azx*,int /*<<< orphan*/ ) ; 
 int azx_readw (struct azx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int azx_single_wait_for_response(struct azx *chip, unsigned int addr)
{
	int timeout = 50;

	while (timeout--) {
		/* check IRV busy bit */
		if (azx_readw(chip, IRS) & AZX_IRS_VALID) {
			/* reuse rirb.res as the response return value */
			azx_bus(chip)->rirb.res[addr] = azx_readl(chip, IR);
			return 0;
		}
		udelay(1);
	}
	if (printk_ratelimit())
		dev_dbg(chip->card->dev, "get_response timeout: IRS=0x%x\n",
			azx_readw(chip, IRS));
	azx_bus(chip)->rirb.res[addr] = -1;
	return -EIO;
}