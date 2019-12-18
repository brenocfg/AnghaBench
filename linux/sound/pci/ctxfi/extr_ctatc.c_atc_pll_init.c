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
struct hw {int (* pll_init ) (struct hw*,int) ;} ;
struct ct_atc {int pll_rate; struct hw* hw; } ;

/* Variables and functions */
 int stub1 (struct hw*,int) ; 

__attribute__((used)) static int atc_pll_init(struct ct_atc *atc, int rate)
{
	struct hw *hw = atc->hw;
	int err;
	err = hw->pll_init(hw, rate);
	atc->pll_rate = err ? 0 : rate;
	return err;
}