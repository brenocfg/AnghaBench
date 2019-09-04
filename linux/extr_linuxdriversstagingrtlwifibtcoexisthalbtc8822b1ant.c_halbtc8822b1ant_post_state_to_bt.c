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
typedef  scalar_t__ u16 ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc8822b1ant_write_score_board (struct btc_coexist*,scalar_t__,int) ; 

__attribute__((used)) static void halbtc8822b1ant_post_state_to_bt(struct btc_coexist *btcoexist,
					     u16 type, bool state)
{
	halbtc8822b1ant_write_score_board(btcoexist, (u16)type, state);
}