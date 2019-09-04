#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int mode; } ;
struct TYPE_6__ {TYPE_2__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct TYPE_4__ {TYPE_3__ enable_attr; } ;
struct ufs_hba {int /*<<< orphan*/  dev; TYPE_1__ clk_scaling; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ufshcd_clkscale_enable_show ; 
 int /*<<< orphan*/  ufshcd_clkscale_enable_store ; 

__attribute__((used)) static void ufshcd_clkscaling_init_sysfs(struct ufs_hba *hba)
{
	hba->clk_scaling.enable_attr.show = ufshcd_clkscale_enable_show;
	hba->clk_scaling.enable_attr.store = ufshcd_clkscale_enable_store;
	sysfs_attr_init(&hba->clk_scaling.enable_attr.attr);
	hba->clk_scaling.enable_attr.attr.name = "clkscale_enable";
	hba->clk_scaling.enable_attr.attr.mode = 0644;
	if (device_create_file(hba->dev, &hba->clk_scaling.enable_attr))
		dev_err(hba->dev, "Failed to create sysfs for clkscale_enable\n");
}