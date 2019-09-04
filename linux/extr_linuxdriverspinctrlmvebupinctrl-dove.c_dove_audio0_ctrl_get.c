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
struct mvebu_mpp_ctrl_data {scalar_t__ base; } ;

/* Variables and functions */
 unsigned long AU0_AC97_SEL ; 
 scalar_t__ PMU_MPP_GENERAL_CTRL ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static int dove_audio0_ctrl_get(struct mvebu_mpp_ctrl_data *data, unsigned pid,
				unsigned long *config)
{
	unsigned long pmu = readl(data->base + PMU_MPP_GENERAL_CTRL);

	*config = ((pmu & AU0_AC97_SEL) != 0);

	return 0;
}