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
struct img_i2s_in {int /*<<< orphan*/  clk_sys; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct img_i2s_in* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int img_i2s_in_runtime_suspend(struct device *dev)
{
	struct img_i2s_in *i2s = dev_get_drvdata(dev);

	clk_disable_unprepare(i2s->clk_sys);

	return 0;
}