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
typedef  int u16 ;

/* Variables and functions */
#define  WCD9335_CDC_RX0_RX_PATH_CTL 145 
#define  WCD9335_CDC_RX0_RX_PATH_MIX_CTL 144 
#define  WCD9335_CDC_RX1_RX_PATH_CTL 143 
#define  WCD9335_CDC_RX1_RX_PATH_MIX_CTL 142 
#define  WCD9335_CDC_RX2_RX_PATH_CTL 141 
#define  WCD9335_CDC_RX2_RX_PATH_MIX_CTL 140 
#define  WCD9335_CDC_RX3_RX_PATH_CTL 139 
#define  WCD9335_CDC_RX3_RX_PATH_MIX_CTL 138 
#define  WCD9335_CDC_RX4_RX_PATH_CTL 137 
#define  WCD9335_CDC_RX4_RX_PATH_MIX_CTL 136 
#define  WCD9335_CDC_RX5_RX_PATH_CTL 135 
#define  WCD9335_CDC_RX5_RX_PATH_MIX_CTL 134 
#define  WCD9335_CDC_RX6_RX_PATH_CTL 133 
#define  WCD9335_CDC_RX6_RX_PATH_MIX_CTL 132 
#define  WCD9335_CDC_RX7_RX_PATH_CTL 131 
#define  WCD9335_CDC_RX7_RX_PATH_MIX_CTL 130 
#define  WCD9335_CDC_RX8_RX_PATH_CTL 129 
#define  WCD9335_CDC_RX8_RX_PATH_MIX_CTL 128 

__attribute__((used)) static u16 wcd9335_interp_get_primary_reg(u16 reg, u16 *ind)
{
	u16 prim_int_reg = WCD9335_CDC_RX0_RX_PATH_CTL;

	switch (reg) {
	case WCD9335_CDC_RX0_RX_PATH_CTL:
	case WCD9335_CDC_RX0_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX0_RX_PATH_CTL;
		*ind = 0;
		break;
	case WCD9335_CDC_RX1_RX_PATH_CTL:
	case WCD9335_CDC_RX1_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX1_RX_PATH_CTL;
		*ind = 1;
		break;
	case WCD9335_CDC_RX2_RX_PATH_CTL:
	case WCD9335_CDC_RX2_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX2_RX_PATH_CTL;
		*ind = 2;
		break;
	case WCD9335_CDC_RX3_RX_PATH_CTL:
	case WCD9335_CDC_RX3_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX3_RX_PATH_CTL;
		*ind = 3;
		break;
	case WCD9335_CDC_RX4_RX_PATH_CTL:
	case WCD9335_CDC_RX4_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX4_RX_PATH_CTL;
		*ind = 4;
		break;
	case WCD9335_CDC_RX5_RX_PATH_CTL:
	case WCD9335_CDC_RX5_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX5_RX_PATH_CTL;
		*ind = 5;
		break;
	case WCD9335_CDC_RX6_RX_PATH_CTL:
	case WCD9335_CDC_RX6_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX6_RX_PATH_CTL;
		*ind = 6;
		break;
	case WCD9335_CDC_RX7_RX_PATH_CTL:
	case WCD9335_CDC_RX7_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX7_RX_PATH_CTL;
		*ind = 7;
		break;
	case WCD9335_CDC_RX8_RX_PATH_CTL:
	case WCD9335_CDC_RX8_RX_PATH_MIX_CTL:
		prim_int_reg = WCD9335_CDC_RX8_RX_PATH_CTL;
		*ind = 8;
		break;
	};

	return prim_int_reg;
}