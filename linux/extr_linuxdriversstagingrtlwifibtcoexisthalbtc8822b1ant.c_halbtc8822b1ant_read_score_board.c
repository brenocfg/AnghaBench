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
struct btc_coexist {int (* btc_read_2byte ) (struct btc_coexist*,int) ;} ;

/* Variables and functions */
 int stub1 (struct btc_coexist*,int) ; 

__attribute__((used)) static void halbtc8822b1ant_read_score_board(struct btc_coexist *btcoexist,
					     u16 *score_board_val)
{
	*score_board_val =
		(btcoexist->btc_read_2byte(btcoexist, 0xaa)) & 0x7fff;
}