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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_RXFIFO ; 
 int /*<<< orphan*/  CHANNEL_TXFIFO ; 
 scalar_t__ REG_IN_ARRAY (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tegra30_ahub_apbif_precious_reg(struct device *dev,
					    unsigned int reg)
{
	if (REG_IN_ARRAY(reg, CHANNEL_TXFIFO) ||
	    REG_IN_ARRAY(reg, CHANNEL_RXFIFO))
		return true;

	return false;
}