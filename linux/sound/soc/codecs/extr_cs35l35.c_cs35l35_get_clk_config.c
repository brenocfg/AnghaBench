#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sysclk; int srate; int clk_cfg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* cs35l35_clk_ctl ; 

__attribute__((used)) static int cs35l35_get_clk_config(int sysclk, int srate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(cs35l35_clk_ctl); i++) {
		if (cs35l35_clk_ctl[i].sysclk == sysclk &&
			cs35l35_clk_ctl[i].srate == srate)
			return cs35l35_clk_ctl[i].clk_cfg;
	}
	return -EINVAL;
}