#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hdac_bus {int /*<<< orphan*/ * last_cmd; } ;
struct azx {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_IRS_BUSY ; 
 int AZX_IRS_VALID ; 
 int EIO ; 
 int /*<<< orphan*/  IC ; 
 int /*<<< orphan*/  IRS ; 
 size_t azx_command_addr (int /*<<< orphan*/ ) ; 
 int azx_readw (struct azx*,int /*<<< orphan*/ ) ; 
 int azx_single_wait_for_response (struct azx*,unsigned int) ; 
 int /*<<< orphan*/  azx_writel (struct azx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_writew (struct azx*,int /*<<< orphan*/ ,int) ; 
 struct azx* bus_to_azx (struct hdac_bus*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int azx_single_send_cmd(struct hdac_bus *bus, u32 val)
{
	struct azx *chip = bus_to_azx(bus);
	unsigned int addr = azx_command_addr(val);
	int timeout = 50;

	bus->last_cmd[azx_command_addr(val)] = val;
	while (timeout--) {
		/* check ICB busy bit */
		if (!((azx_readw(chip, IRS) & AZX_IRS_BUSY))) {
			/* Clear IRV valid bit */
			azx_writew(chip, IRS, azx_readw(chip, IRS) |
				   AZX_IRS_VALID);
			azx_writel(chip, IC, val);
			azx_writew(chip, IRS, azx_readw(chip, IRS) |
				   AZX_IRS_BUSY);
			return azx_single_wait_for_response(chip, addr);
		}
		udelay(1);
	}
	if (printk_ratelimit())
		dev_dbg(chip->card->dev,
			"send_cmd timeout: IRS=0x%x, val=0x%x\n",
			azx_readw(chip, IRS), val);
	return -EIO;
}