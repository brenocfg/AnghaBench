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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;
struct davinci_mcasp {int /*<<< orphan*/  auxclk_fs_ratio; TYPE_1__* dev; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_mcasp_get_dt_params(struct davinci_mcasp *mcasp)
{
	struct device_node *np = mcasp->dev->of_node;
	int ret;
	u32 val;

	if (!np)
		return 0;

	ret = of_property_read_u32(np, "auxclk-fs-ratio", &val);
	if (ret >= 0)
		mcasp->auxclk_fs_ratio = val;

	return 0;
}