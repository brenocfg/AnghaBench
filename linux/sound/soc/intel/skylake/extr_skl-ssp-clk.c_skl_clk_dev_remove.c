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
struct skl_clk_data {int /*<<< orphan*/  parent; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_MAX_CLK_SRC ; 
 struct skl_clk_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_parent_src_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_src_clk (struct skl_clk_data*) ; 

__attribute__((used)) static int skl_clk_dev_remove(struct platform_device *pdev)
{
	struct skl_clk_data *data;

	data = platform_get_drvdata(pdev);
	unregister_src_clk(data);
	unregister_parent_src_clk(data->parent, SKL_MAX_CLK_SRC);

	return 0;
}