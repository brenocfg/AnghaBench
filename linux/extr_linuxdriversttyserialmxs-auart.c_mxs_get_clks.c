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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mxs_auart_port {void* clk_ahb; int /*<<< orphan*/ * dev; void* clk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int clk_set_rate (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_asm9260_auart (struct mxs_auart_port*) ; 

__attribute__((used)) static int mxs_get_clks(struct mxs_auart_port *s,
			struct platform_device *pdev)
{
	int err;

	if (!is_asm9260_auart(s)) {
		s->clk = devm_clk_get(&pdev->dev, NULL);
		return PTR_ERR_OR_ZERO(s->clk);
	}

	s->clk = devm_clk_get(s->dev, "mod");
	if (IS_ERR(s->clk)) {
		dev_err(s->dev, "Failed to get \"mod\" clk\n");
		return PTR_ERR(s->clk);
	}

	s->clk_ahb = devm_clk_get(s->dev, "ahb");
	if (IS_ERR(s->clk_ahb)) {
		dev_err(s->dev, "Failed to get \"ahb\" clk\n");
		return PTR_ERR(s->clk_ahb);
	}

	err = clk_prepare_enable(s->clk_ahb);
	if (err) {
		dev_err(s->dev, "Failed to enable ahb_clk!\n");
		return err;
	}

	err = clk_set_rate(s->clk, clk_get_rate(s->clk_ahb));
	if (err) {
		dev_err(s->dev, "Failed to set rate!\n");
		goto disable_clk_ahb;
	}

	err = clk_prepare_enable(s->clk);
	if (err) {
		dev_err(s->dev, "Failed to enable clk!\n");
		goto disable_clk_ahb;
	}

	return 0;

disable_clk_ahb:
	clk_disable_unprepare(s->clk_ahb);
	return err;
}