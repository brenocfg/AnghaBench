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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EDATA (int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int qm_ccsr_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_edata_bits(struct device *dev, u32 bit_count)
{
	u32 i, j, mask = 0xffffffff;

	dev_warn(dev, "ErrInt, EDATA:\n");
	i = bit_count / 32;
	if (bit_count % 32) {
		i++;
		mask = ~(mask << bit_count % 32);
	}
	j = 16 - i;
	dev_warn(dev, "  0x%08x\n", qm_ccsr_in(REG_EDATA(j)) & mask);
	j++;
	for (; j < 16; j++)
		dev_warn(dev, "  0x%08x\n", qm_ccsr_in(REG_EDATA(j)));
}