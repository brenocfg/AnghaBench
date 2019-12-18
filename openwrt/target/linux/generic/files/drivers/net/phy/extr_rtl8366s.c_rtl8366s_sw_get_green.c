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
typedef  int u32 ;
struct TYPE_2__ {int i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8366S_GREEN_ETHERNET_CTRL_REG ; 
 int RTL8366S_GREEN_ETHERNET_RX_BIT ; 
 int RTL8366S_GREEN_ETHERNET_TX_BIT ; 
 int rtl8366_smi_read_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int*) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

__attribute__((used)) static int rtl8366s_sw_get_green(struct switch_dev *dev,
			      const struct switch_attr *attr,
			      struct switch_val *val)
{
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	u32 data;
	int err;

	err = rtl8366_smi_read_reg(smi, RTL8366S_GREEN_ETHERNET_CTRL_REG, &data);
	if (err)
		return err;

	val->value.i = ((data & (RTL8366S_GREEN_ETHERNET_TX_BIT | RTL8366S_GREEN_ETHERNET_RX_BIT)) != 0) ? 1 : 0;

	return 0;
}