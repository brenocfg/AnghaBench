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
struct hw {int (* mic_source_switch_put ) (struct hw*,int) ;} ;
struct ct_atc {struct hw* hw; } ;

/* Variables and functions */
 int stub1 (struct hw*,int) ; 

__attribute__((used)) static int atc_mic_source_switch_put(struct ct_atc *atc, int position)
{
	struct hw *hw = atc->hw;

	return hw->mic_source_switch_put(hw, position);
}