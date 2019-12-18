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
struct rtl8366_smi {scalar_t__ ext_mbus; } ;

/* Variables and functions */
 int __rtl8366_mdio_read_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __rtl8366_smi_read_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rtl8366_smi_read_reg(struct rtl8366_smi *smi, u32 addr, u32 *data)
{
	if (smi->ext_mbus)
		return __rtl8366_mdio_read_reg(smi, addr, data);
	else
		return __rtl8366_smi_read_reg(smi, addr, data);
}