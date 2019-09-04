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

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int /*<<< orphan*/  SOC_DTS_OFFSET_ENABLE ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int soc_dts_enable(int id)
{
	u32 out;
	int ret;

	ret = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ,
			    SOC_DTS_OFFSET_ENABLE, &out);
	if (ret)
		return ret;

	if (!(out & BIT(id))) {
		out |= BIT(id);
		ret = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				     SOC_DTS_OFFSET_ENABLE, out);
		if (ret)
			return ret;
	}

	return ret;
}