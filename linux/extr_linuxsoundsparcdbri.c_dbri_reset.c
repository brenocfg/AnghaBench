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
struct snd_dbri {scalar_t__ regs; } ;

/* Variables and functions */
 int D_E ; 
 int D_G ; 
 int /*<<< orphan*/  D_GEN ; 
 int D_R ; 
 int D_S ; 
 scalar_t__ REG0 ; 
 scalar_t__ REG2 ; 
 scalar_t__ REG8 ; 
 scalar_t__ REG9 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int sbus_readl (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dbri_reset(struct snd_dbri *dbri)
{
	int i;
	u32 tmp;

	dprintk(D_GEN, "reset 0:%x 2:%x 8:%x 9:%x\n",
		sbus_readl(dbri->regs + REG0),
		sbus_readl(dbri->regs + REG2),
		sbus_readl(dbri->regs + REG8), sbus_readl(dbri->regs + REG9));

	sbus_writel(D_R, dbri->regs + REG0);	/* Soft Reset */
	for (i = 0; (sbus_readl(dbri->regs + REG0) & D_R) && i < 64; i++)
		udelay(10);

	/* A brute approach - DBRI falls back to working burst size by itself
	 * On SS20 D_S does not work, so do not try so high. */
	tmp = sbus_readl(dbri->regs + REG0);
	tmp |= D_G | D_E;
	tmp &= ~D_S;
	sbus_writel(tmp, dbri->regs + REG0);
}