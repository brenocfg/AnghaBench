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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtc8822b2ant_set_coex_table(struct btc_coexist *btcoexist,
					   u32 val0x6c0, u32 val0x6c4,
					   u32 val0x6c8, u8 val0x6cc)
{
	btcoexist->btc_write_4byte(btcoexist, 0x6c0, val0x6c0);

	btcoexist->btc_write_4byte(btcoexist, 0x6c4, val0x6c4);

	btcoexist->btc_write_4byte(btcoexist, 0x6c8, val0x6c8);

	btcoexist->btc_write_1byte(btcoexist, 0x6cc, val0x6cc);
}