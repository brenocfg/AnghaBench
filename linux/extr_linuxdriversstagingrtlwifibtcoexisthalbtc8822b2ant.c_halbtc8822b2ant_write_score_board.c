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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_2byte ) (struct btc_coexist*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void halbtc8822b2ant_write_score_board(struct btc_coexist *btcoexist,
					      u16 bitpos, bool state)
{
	static u16 originalval = 0x8002;

	if (state)
		originalval = originalval | bitpos;
	else
		originalval = originalval & (~bitpos);

	btcoexist->btc_write_2byte(btcoexist, 0xaa, originalval);
}