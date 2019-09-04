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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8822b1ant_low_penalty_ra (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void halbtc8822b1ant_sw_mechanism(struct btc_coexist *btcoexist,
					 bool low_penalty_ra)
{
	halbtc8822b1ant_low_penalty_ra(btcoexist, NORMAL_EXEC, low_penalty_ra);
}