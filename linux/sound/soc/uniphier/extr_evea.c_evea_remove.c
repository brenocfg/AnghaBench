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
struct platform_device {int dummy; } ;
struct evea_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_exiv; int /*<<< orphan*/  rst; int /*<<< orphan*/  rst_exiv; int /*<<< orphan*/  rst_adamv; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct evea_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evea_remove(struct platform_device *pdev)
{
	struct evea_priv *evea = platform_get_drvdata(pdev);

	reset_control_assert(evea->rst_adamv);
	reset_control_assert(evea->rst_exiv);
	reset_control_assert(evea->rst);

	clk_disable_unprepare(evea->clk_exiv);
	clk_disable_unprepare(evea->clk);

	return 0;
}