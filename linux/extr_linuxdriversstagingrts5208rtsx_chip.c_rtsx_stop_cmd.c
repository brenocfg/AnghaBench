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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMACTL ; 
 int /*<<< orphan*/  RBCTL ; 
 int RTSX_HCBAR ; 
 int /*<<< orphan*/  RTSX_HCBCTLR ; 
 int /*<<< orphan*/  RTSX_HDBCTLR ; 
 int /*<<< orphan*/  STOP_CMD ; 
 int /*<<< orphan*/  STOP_DMA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_read_register (struct rtsx_chip*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtsx_readl (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_writel (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtsx_stop_cmd(struct rtsx_chip *chip, int card)
{
	int i;

	for (i = 0; i <= 8; i++) {
		int addr = RTSX_HCBAR + i * 4;
		u32 reg;

		reg = rtsx_readl(chip, addr);
		dev_dbg(rtsx_dev(chip), "BAR (0x%02x): 0x%08x\n", addr, reg);
	}
	rtsx_writel(chip, RTSX_HCBCTLR, STOP_CMD);
	rtsx_writel(chip, RTSX_HDBCTLR, STOP_DMA);

	for (i = 0; i < 16; i++) {
		u16 addr = 0xFE20 + (u16)i;
		u8 val;

		rtsx_read_register(chip, addr, &val);
		dev_dbg(rtsx_dev(chip), "0x%04X: 0x%02x\n", addr, val);
	}

	rtsx_write_register(chip, DMACTL, 0x80, 0x80);
	rtsx_write_register(chip, RBCTL, 0x80, 0x80);
}