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
typedef  int /*<<< orphan*/  u32 ;
struct atlas7_pmx {int dummy; } ;
struct atlas7_pad_config {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PAD_T_AD ; 
 int __atlas7_pmx_pin_ad_sel (struct atlas7_pmx*,struct atlas7_pad_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __atlas7_pmx_pin_digital_enable(struct atlas7_pmx *pmx,
			struct atlas7_pad_config *conf, u32 bank)
{
	/* Other type pads are always digital */
	if (conf->type != PAD_T_AD)
		return 0;

	return __atlas7_pmx_pin_ad_sel(pmx, conf, bank, 1);
}