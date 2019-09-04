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
struct rtl_fw_phy_action {size_t size; int /*<<< orphan*/ * code; } ;
struct rtl_fw {struct rtl_fw_phy_action phy_action; } ;
struct mdio_ops {int /*<<< orphan*/  read; int /*<<< orphan*/  write; } ;
struct rtl8169_private {struct mdio_ops mdio_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  PHY_BJMPN 140 
#define  PHY_CLEAR_READCOUNT 139 
#define  PHY_COMP_EQ_SKIPN 138 
#define  PHY_COMP_NEQ_SKIPN 137 
#define  PHY_DATA_AND 136 
#define  PHY_DATA_OR 135 
#define  PHY_DELAY_MS 134 
#define  PHY_MDIO_CHG 133 
#define  PHY_READ 132 
#define  PHY_READCOUNT_EQ_SKIP 131 
#define  PHY_SKIPN 130 
#define  PHY_WRITE 129 
#define  PHY_WRITE_PREVIOUS 128 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_mcu_read ; 
 int /*<<< orphan*/  mac_mcu_write ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl_readphy (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl_phy_write_fw(struct rtl8169_private *tp, struct rtl_fw *rtl_fw)
{
	struct rtl_fw_phy_action *pa = &rtl_fw->phy_action;
	struct mdio_ops org, *ops = &tp->mdio_ops;
	u32 predata, count;
	size_t index;

	predata = count = 0;
	org.write = ops->write;
	org.read = ops->read;

	for (index = 0; index < pa->size; ) {
		u32 action = le32_to_cpu(pa->code[index]);
		u32 data = action & 0x0000ffff;
		u32 regno = (action & 0x0fff0000) >> 16;

		if (!action)
			break;

		switch(action & 0xf0000000) {
		case PHY_READ:
			predata = rtl_readphy(tp, regno);
			count++;
			index++;
			break;
		case PHY_DATA_OR:
			predata |= data;
			index++;
			break;
		case PHY_DATA_AND:
			predata &= data;
			index++;
			break;
		case PHY_BJMPN:
			index -= regno;
			break;
		case PHY_MDIO_CHG:
			if (data == 0) {
				ops->write = org.write;
				ops->read = org.read;
			} else if (data == 1) {
				ops->write = mac_mcu_write;
				ops->read = mac_mcu_read;
			}

			index++;
			break;
		case PHY_CLEAR_READCOUNT:
			count = 0;
			index++;
			break;
		case PHY_WRITE:
			rtl_writephy(tp, regno, data);
			index++;
			break;
		case PHY_READCOUNT_EQ_SKIP:
			index += (count == data) ? 2 : 1;
			break;
		case PHY_COMP_EQ_SKIPN:
			if (predata == data)
				index += regno;
			index++;
			break;
		case PHY_COMP_NEQ_SKIPN:
			if (predata != data)
				index += regno;
			index++;
			break;
		case PHY_WRITE_PREVIOUS:
			rtl_writephy(tp, regno, predata);
			index++;
			break;
		case PHY_SKIPN:
			index += regno + 1;
			break;
		case PHY_DELAY_MS:
			mdelay(data);
			index++;
			break;

		default:
			BUG();
		}
	}

	ops->write = org.write;
	ops->read = org.read;
}