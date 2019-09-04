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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  bt_chip_type; } ;
struct btc_coexist {TYPE_1__ board_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_CHIP_CSR_BC4 ; 
 int /*<<< orphan*/  BTC_CHIP_CSR_BC8 ; 
 int /*<<< orphan*/  BTC_CHIP_RTL8723A ; 
 int /*<<< orphan*/  BTC_CHIP_RTL8723B ; 
 int /*<<< orphan*/  BTC_CHIP_RTL8821 ; 
 int /*<<< orphan*/  BTC_CHIP_UNDEF ; 
#define  BT_2WIRE 136 
#define  BT_ACCEL 135 
#define  BT_CSR_BC4 134 
#define  BT_CSR_BC8 133 
#define  BT_ISSC_3WIRE 132 
#define  BT_RTL8723A 131 
#define  BT_RTL8723B 130 
#define  BT_RTL8756 129 
#define  BT_RTL8821A 128 

void exhalbtc_set_chip_type(struct btc_coexist *btcoexist, u8 chip_type)
{
	switch (chip_type) {
	default:
	case BT_2WIRE:
	case BT_ISSC_3WIRE:
	case BT_ACCEL:
	case BT_RTL8756:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_UNDEF;
		break;
	case BT_CSR_BC4:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_CSR_BC4;
		break;
	case BT_CSR_BC8:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_CSR_BC8;
		break;
	case BT_RTL8723A:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_RTL8723A;
		break;
	case BT_RTL8821A:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_RTL8821;
		break;
	case BT_RTL8723B:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_RTL8723B;
		break;
	}
}