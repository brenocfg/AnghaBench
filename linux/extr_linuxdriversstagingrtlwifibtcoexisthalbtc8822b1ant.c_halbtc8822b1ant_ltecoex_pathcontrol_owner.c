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
typedef  int u8 ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void
halbtc8822b1ant_ltecoex_pathcontrol_owner(struct btc_coexist *btcoexist,
					  bool wifi_control)
{
	u8 val;

	val = (wifi_control) ? 1 : 0;
	/* 0x70[26] */
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x73, 0x4, val);
}