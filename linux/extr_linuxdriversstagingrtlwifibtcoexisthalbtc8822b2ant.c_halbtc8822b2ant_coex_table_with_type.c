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
typedef  int u32 ;
struct btc_coexist {int dummy; } ;
struct TYPE_2__ {int coex_table_type; scalar_t__ concurrent_rx_mode_on; } ;

/* Variables and functions */
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_coex_table (struct btc_coexist*,int,int,int,int,int) ; 

__attribute__((used)) static void halbtc8822b2ant_coex_table_with_type(struct btc_coexist *btcoexist,
						 bool force_exec, u8 type)
{
	u32 break_table;
	u8 select_table;

	coex_sta->coex_table_type = type;

	if (coex_sta->concurrent_rx_mode_on) {
		break_table = 0xf0ffffff; /* set WL hi-pri can break BT */
		/* set Tx response = Hi-Pri (ex: Transmitting ACK,BA,CTS) */
		select_table = 0xb;
	} else {
		break_table = 0xffffff;
		select_table = 0x3;
	}

	switch (type) {
	case 0:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0xffffffff,
					   0xffffffff, break_table,
					   select_table);
		break;
	case 1:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 2:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x5a5a5a5a,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 3:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 4:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a5a5a, break_table,
					   select_table);
		break;
	case 5:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x55555555, break_table,
					   select_table);
		break;
	case 6:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0xa5555555,
					   0xfafafafa, break_table,
					   select_table);
		break;
	case 7:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0xa5555555,
					   0xaa5a5a5a, break_table,
					   select_table);
		break;
	case 8:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0xa5555555,
					   0xfafafafa, break_table,
					   select_table);
		break;
	case 9:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x5a5a5a5a,
					   0xaaaa5aaa, break_table,
					   select_table);
		break;
	case 10:
		halbtc8822b2ant_coex_table(btcoexist, force_exec, 0x55555555,
					   0x5a5a555a, break_table,
					   select_table);
		break;
	default:
		break;
	}
}