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
struct db2k_private {scalar_t__ plx; } ;
struct comedi_device {struct db2k_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLX_CNTRL_EERELOAD ; 
 scalar_t__ PLX_REG_CNTRL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void db2k_reload_plx(struct comedi_device *dev)
{
	struct db2k_private *devpriv = dev->private;
	u32 cntrl;

	cntrl = readl(devpriv->plx + PLX_REG_CNTRL);
	cntrl &= ~PLX_CNTRL_EERELOAD;
	writel(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
	cntrl |= PLX_CNTRL_EERELOAD;
	writel(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
	cntrl &= ~PLX_CNTRL_EERELOAD;
	writel(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
}