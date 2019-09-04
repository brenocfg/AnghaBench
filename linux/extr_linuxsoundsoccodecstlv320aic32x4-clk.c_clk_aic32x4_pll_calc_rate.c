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
typedef  int u64 ;
struct clk_aic32x4_pll_muldiv {int r; int j; int d; int p; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP_ULL (int,int) ; 

__attribute__((used)) static unsigned long clk_aic32x4_pll_calc_rate(
			struct clk_aic32x4_pll_muldiv *settings,
			unsigned long parent_rate)
{
	u64 rate;
	/*
	 * We scale j by 10000 to account for the decimal part of P and divide
	 * it back out later.
	 */
	rate = (u64) parent_rate * settings->r *
				((settings->j * 10000) + settings->d);

	return (unsigned long) DIV_ROUND_UP_ULL(rate, settings->p * 10000);
}