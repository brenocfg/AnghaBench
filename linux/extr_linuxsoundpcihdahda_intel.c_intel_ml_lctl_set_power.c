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
struct hdac_bus {scalar_t__ mlcap; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 int AZX_MLCTL_CPA ; 
 int AZX_MLCTL_CPA_SHIFT ; 
 int AZX_MLCTL_SPA ; 
 int AZX_MLCTL_SPA_SHIFT ; 
 scalar_t__ AZX_ML_BASE ; 
 scalar_t__ AZX_REG_ML_LCTL ; 
 struct hdac_bus* azx_bus (struct azx*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int intel_ml_lctl_set_power(struct azx *chip, int state)
{
	struct hdac_bus *bus = azx_bus(chip);
	u32 val;
	int timeout;

	/*
	 * the codecs are sharing the first link setting by default
	 * If other links are enabled for stream, they need similar fix
	 */
	val = readl(bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL);
	val &= ~AZX_MLCTL_SPA;
	val |= state << AZX_MLCTL_SPA_SHIFT;
	writel(val, bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL);
	/* wait for CPA */
	timeout = 50;
	while (timeout) {
		if (((readl(bus->mlcap + AZX_ML_BASE + AZX_REG_ML_LCTL)) &
		    AZX_MLCTL_CPA) == (state << AZX_MLCTL_CPA_SHIFT))
			return 0;
		timeout--;
		udelay(10);
	}

	return -1;
}