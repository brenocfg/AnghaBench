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
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_RESET_BBP ; 
 int MT_MAC_SYS_CTRL_RESET_CSR ; 
 int /*<<< orphan*/  MT_PBF_SYS_CTRL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x0_reset_csr_bbp(struct mt76x0_dev *dev)
{
	u32 val;

	val = mt76_rr(dev, MT_PBF_SYS_CTRL);
	val &= ~0x2000;
	mt76_wr(dev, MT_PBF_SYS_CTRL, val);

	mt76_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_RESET_CSR |
					 MT_MAC_SYS_CTRL_RESET_BBP);

	msleep(200);
}