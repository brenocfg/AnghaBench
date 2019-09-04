#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int snpsid; } ;
struct dwc2_hsotg {TYPE_1__ hw_params; } ;

/* Variables and functions */

__attribute__((used)) static inline bool dwc2_is_iot(struct dwc2_hsotg *hsotg)
{
	return (hsotg->hw_params.snpsid & 0xfff00000) == 0x55300000;
}