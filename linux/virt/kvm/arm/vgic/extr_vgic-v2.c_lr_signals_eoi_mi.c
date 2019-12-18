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
typedef  int u32 ;

/* Variables and functions */
 int GICH_LR_EOI ; 
 int GICH_LR_HW ; 
 int GICH_LR_STATE ; 

__attribute__((used)) static bool lr_signals_eoi_mi(u32 lr_val)
{
	return !(lr_val & GICH_LR_STATE) && (lr_val & GICH_LR_EOI) &&
	       !(lr_val & GICH_LR_HW);
}