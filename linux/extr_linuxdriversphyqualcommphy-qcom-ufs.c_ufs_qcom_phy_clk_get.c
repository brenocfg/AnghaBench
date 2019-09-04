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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int __ufs_qcom_phy_clk_get (struct device*,char const*,struct clk**,int) ; 

__attribute__((used)) static int ufs_qcom_phy_clk_get(struct device *dev,
			 const char *name, struct clk **clk_out)
{
	return __ufs_qcom_phy_clk_get(dev, name, clk_out, true);
}